#version 330 core
out vec4 FragColor;

uniform float intensity;
uniform vec4 grid_color;
uniform vec4 dipole_color;
uniform bool grid;
uniform bool dipole;
uniform float max_inte;

void main()
{

	if (grid == true )
	{
		FragColor = grid_color;
	}
	else if (grid == false )
	{

		float inc = 6.0 * max_inte;
		float x = intensity * inc;
		float r = 0.0f; float g = 0.0f; float b = 0.0f;
	   
		if ((0 <= x && x <= 1) || (5 <= x && x <= 6))
			r = 1.0f;

	    	else if (4 <= x && x <= 5) 
			r = x - 4.0f;

	    	else if (1 <= x && x <= 2) 
			r = 1.0f - (x - 1.0f);

	    	if (1 <= x && x <= 3) 
			g = 1.0f;

	    	else if (0 <= x && x <= 1) 
			g = x - 0.0f;

	    	else if (3 <= x && x <= 4) 
			g = 1.0f - (x - 3.0f);

	    	if (3 <= x && x <= 5) 
			b = 1.0f;

	    	else if (2 <= x && x <= 3) 
			b = x - 2.0f;

	    	else if (5 <= x && x <= 6) 
			b = 1.0f - (x - 5.0f);

		if (dipole == true )
		{
			FragColor = dipole_color;
		}		
		else if (dipole == false )
		{		
			FragColor = vec4(r, g, b, 1.0f);
		}
	}
}









