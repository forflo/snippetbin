/*
	Jwakeonlan - Accepts three arguments, parses them and sends a special 
	networkpacket to wake up a computer from S5
	
    Copyright (C) 2012  Florian Mayer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

package netUtils;

import java.net.*;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Jwakeonlan {
	public static final String[] ALLOWED_DELIMITERS = { ":", "_", ";", "-", "\\." };
	public static final String MAGEX = "[0-9a-fA-F]";
	public static final String STDIP = "255.255.255.255";
	public static final int STDPORT = 9;
	public static final String USERTEXT = "usage: java wakeonlan mac-address [ ip-address [port]] "
			+ "\ne.g:\tjava wakeonlan 00:00:12:12:33:ee 192.168.112.255"
			+ "\n\t\t=> sends the packet to the broadcast using the port 9" + "\n\tjava wakeonlan 00:12:12:12:33:ff"
			+ "\n\t\t=> sends the packet to the address '255.255.255.255'";

	/* 
	 * Main --- For cmdline usage ...
	 * Catches two kinds of Exception (see below)
	 * and ends with a return value != 0
	 * thus it can be used in a shell skript for
	 * waking up some remote computers
	 */
	public static void main(String[] args) {
		try {
			if (args.length == 3) {
				byte[] macAddr = getMagicPacket(args[0]);
				sendPacket(macAddr, InetAddress.getByName(args[1]), Integer.parseInt(args[2]));
			} else if (args.length == 2) {
				byte[] macAddr = getMagicPacket(args[0]);
				sendPacket(macAddr, InetAddress.getByName(args[1]));
			} else if (args.length == 1) {
				byte[] macAddr = getMagicPacket(args[0]);
				sendPacket(macAddr);
			} else {
				System.out.println(USERTEXT);
				System.exit(1);
			}
		} catch (IllegalArgumentException e) {
			// Weil Kommandozeilentool, retrun != 0 ...
			System.out.println("Fehler: " + e.getMessage());
			System.exit(1);
		} catch (UnknownHostException f){
			System.out.println("Fehler beim Erstellen eines InetAddress Objektes: Host ist unbekannt");
			System.exit(1);
		}
	}

	// sends the magicpacket to "STDIP" using the "STDPORT"
	public static void sendPacket(byte[] data) {
		try {
			DatagramSocket soc = new DatagramSocket();
			DatagramPacket packet = new DatagramPacket(data, data.length, InetAddress.getByName(STDIP), STDPORT);
			soc.send(packet);
		} catch (Exception e) {
			System.out.println("Das Senden des Paketes ist fehlgeschlagen ...");
		}
	}

	// uses "STDPORT"
	public static void sendPacket(byte[] data, InetAddress ip) {
		try {
			DatagramSocket soc = new DatagramSocket();
			DatagramPacket packet = new DatagramPacket(data, data.length, ip, STDPORT);
			soc.send(packet);
		} catch (Exception e) {
			System.out.println("Das Senden des Paketes ist fehlgeschlagen ...");
		}
	}

	// is completely parameterized
	public static void sendPacket(byte[] data, InetAddress ip, int port) {
		try {
			DatagramSocket soc = new DatagramSocket();
			DatagramPacket packet = new DatagramPacket(data, data.length, ip, port);
			soc.send(packet);
		} catch (Exception e) {
			System.out.println("Das Senden des Paketes ist fehlgeschlagen ...");
		}
	}

	/*
	 * prüft die Formatierung des Strings "mac". Es gibt mehrere Wege die
	 * Mac-Adresse zu schreiben. z.B. 00-01-02-03-04-05 oder 00:00:00:00:00:00
	 * oder 34.32.11.32.45.32 etc.
	 * 
	 * Diese Methode unterstützt die im Feld "AllowedDelimiters" angegebenen
	 * Methoden der Trennung.
	 * 
	 * Gibt "false" zurück, wenn der reguläre Ausdruck "MAGEX" nicht auf "mac"
	 * zutrifft oder wenn ein falsches Trennzeichen verwendet wurde, ansonsten
	 * "true"...
	 */
	public static boolean checkFormat(String mac) {
		String hilf = MAGEX + MAGEX;
		for (String d : ALLOWED_DELIMITERS) {
			Pattern macPat = Pattern.compile(hilf + d + hilf + d + hilf + d + hilf + d + hilf + d + hilf);
			Matcher m = macPat.matcher(mac);
			if (m.matches())
				return true;
		}
		return false;
	}

	/*
	 * Gibt das Trennzeichen zurück, dass in der Mac-Addresse verwendet wurde
	 * ... Gibt null zurück, falls das Format ungültig ist, oder ein falsches
	 * Trennzeichen verwendet wurde
	 * 
	 * Zugegeben etwas redundant ...
	 * Man könnte auch nur diese Funktion verwenden um die Integrität von "mac"
	 * zu prüfen. "mac" ist dann falsch formatiert, wenn getDelimiter("blae") == null
	 * Ich finde es nur getrennt schöner...
	 */
	public static String getDelimiter(String mac) {
		String hilf = MAGEX + MAGEX;
		for (String d : ALLOWED_DELIMITERS) {
			Pattern macPat = Pattern.compile(hilf + d + hilf + d + hilf + d + hilf + d + hilf + d + hilf);
			Matcher m = macPat.matcher(mac);
			if (m.matches())
				return d;
		}
		return null;
	}

	/*
	 * Gibt das MagicPacket der in "mac" gespeicherten Mac-Adresse als Bytefeld
	 * zurück. Schreibt einen Fehler auf stdout, wenn die übergebene Mac-Adresse
	 * nicht gültig ist, oder das falsche Trennzeichen
	 * (siehe "AllowedDelimiters") verwendet wurde und schmeißt eine Ausnahme.
	 */
	public static byte[] getMagicPacket(String mac) throws IllegalArgumentException {
		if (!checkFormat(mac)) {
			throw new IllegalArgumentException("Bad mac-address format: " + mac);
		}

		int z = 0;
		int i = 0;
		byte[] result = new byte[102]; 	// Magic-Packet
		byte[] macAddr = new byte[6]; 	// Byte representation of the mac-address
		StringTokenizer tok = new StringTokenizer(mac, getDelimiter(mac));

		// Umwandeln der Mac-Adresse in sechs bytes
		while (tok.hasMoreTokens()) {
			byte hilf = (byte) Integer.parseInt(tok.nextToken(), 16);
			macAddr[z++] = hilf;
		}

		// Die ersten 6 Byte des MagicPacketes sind 0xFF
		// Danach folgt 16 mal die hexadezimale Darstellung der Mac-Adresse
		// des aufzuweckenden Computers (siehe wikipedia ---> wakeonlan)
		for (int j = 0; j < 6; j++)
			result[i++] = (byte) 0xFF;
		for (int j = 0; j < 16; j++)
			for (int k = 0; k < 6; k++)
				result[i++] = macAddr[k];

		return result;
	}
}

