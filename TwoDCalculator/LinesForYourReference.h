
const float span = .3;

// Vertices and lines:
Vector2D bottomLeft(-span, -span);
Vector2D topLeft(-span, span);
Vector2D topRight(span, span);
Vector2D bottomRight(span, -span);
Vector2D roofTop(0, span + .25);

Vector2D lines[] = { 
	bottomLeft, topLeft,
	topLeft, topRight,
	topRight, bottomRight,
	bottomRight, bottomLeft,
	topLeft, roofTop,
	topRight, roofTop
};

int numLines = sizeof(lines) / (sizeof(*lines) * 2);
