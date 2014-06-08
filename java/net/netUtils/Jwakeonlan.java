/*
	Jwakeonlan - Accepts three arguments, parses them and sends a special 
	Networkpacket to wake up a computer from S5
	
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

	// Main
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
		} catch (Exception e) {
			// Weil Kommandozeilentool, retrun != 0 ...
			System.exit(1);
		}
	}

	// Sendet das Magik Packet an die STDIP mit STDPORT
	public static void sendPacket(byte[] data) {
		try {
			DatagramSocket soc = new DatagramSocket();
			DatagramPacket packet = new DatagramPacket(data, data.length, InetAddress.getByName(STDIP), STDPORT);
			soc.send(packet);
		} catch (Exception e) {
			System.out.println("Das Senden des Paketes ist fehlgeschlagen ...");
		}
	}

	// Verwendet STDPORT
	public static void sendPacket(byte[] data, InetAddress ip) {
		try {
			DatagramSocket soc = new DatagramSocket();
			DatagramPacket packet = new DatagramPacket(data, data.length, ip, STDPORT);
			soc.send(packet);
		} catch (Exception e) {
			System.out.println("Das Senden des Paketes ist fehlgeschlagen ...");
		}
	}

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
	 * Gibt das Trennzeichen zurück, dass in der Mac-Addresse
	 * verwendet wurde ...
	 * Gibt null zurück, falls das Format ungültig ist, oder
	 * ein falsches Trennzeichen verwendet wurde
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
	 * nicht gültig ist, oder das falsche Trennzeichen (siehe
	 * "AllowedDelimiters") verwendet wurde
	 */
	public static byte[] getMagicPacket(String mac) throws IllegalArgumentException {
		if (! checkFormat(mac)) {
			System.out.println("Die Mac-Adresse hat ein falsches Format, oder Trennzeichen ...");
			throw new IllegalArgumentException("Bad mac-address format: " + mac);
		}
		StringTokenizer tok = new StringTokenizer(mac, getDelimiter(mac));

		byte[] result = new byte[102]; // Magic-Packet
		byte[] macAddr = new byte[6]; // Byte representation of the mac-address
										// given as String

		// Umwandeln der Mac-Adresse in sechs bytes
		int i = 0;
		while (tok.hasMoreTokens()) {
			byte hilf = (byte) Integer.parseInt(tok.nextToken(), 16);
			macAddr[i++] = hilf;
		}

		// Die ersten 6 Byte des MagicPacketes sind 0xFF
		// Danach folgt 16 mal die hexadezimale Darstellung der Mac-Adresse
		// des aufzuweckenden Computers
		i = 0;
		for (int j = 0; j < 6; j++)
			result[i++] = (byte) 0xFF; // result[0-5] = 1111 1111
		for (int j = 0; j < 16; j++)
			for (int k = 0; k < 6; k++)
				result[i++] = macAddr[k];

		return result;
	}
}

