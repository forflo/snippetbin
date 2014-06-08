var eval_increase = function (program) {
	var p = getProgramObject(program);
	var currentValue = getValAtPos(p.x, p.y);
	var delta = gaussianFunction(currentValue, 18, 127, 30, 2); // range 2 to 20, centered at 127, "width" of 30
	delta = Math.ceil(delta);
	if (program == 1) {
		currentValue += delta;
	} else {
		currentValue -= delta;
	}
	if (currentValue > 255) {
		currentValue = 255;
	}
	if (currentValue < 0) {
		currentValue = 0;
	}
	var difference = currentValue - getValAtPos(p.x, p.y);
	env.sum[env.stage-1] += difference;
	setValAtPos(p.x, p.y, currentValue);
};

// from http://en.wikipedia.org/wiki/Gaussian_function
// a: height of curve, 
// b: center position, 
// c: width of bell curve
// d: constant minimum height
var gaussianFunction = function (x, a, b, c, d) {
	var e = 2.7182818;
	return d + (a * Math.pow(e, -(((x-b)*(x-b))/(2*(c*c)))));
}
