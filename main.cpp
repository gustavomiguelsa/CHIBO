//==================================================================================================================
//Electric Field Visualizer - CHIBO - Version 1.0
//Author: Gustavo Assunção
//
//An OpenGL implementation of Electric Field Visualization, generated by a dipole located under a membrane, on a set
//of detectors placed on that same membrane
//
//OpenGL 3.3 used, with GLFW, glad and glm support
//==================================================================================================================

#include </home/gustavo/Desktop/opengl_prj/glad.h>      //glad must always be included before other libraries
#include </home/gustavo/Desktop/opengl_prj/glfw3.h>

#include </home/gustavo/Desktop/opengl_prj/window.h>
#define STB_IMAGE_IMPLEMENTATION    //To implement the code to be compiled
#include </home/gustavo/Desktop/opengl_prj/stb_image.h>

#include </home/gustavo/Desktop/opengl_prj/glm/glm.hpp>
#include </home/gustavo/Desktop/opengl_prj/glm/gtc/matrix_transform.hpp>
#include </home/gustavo/Desktop/opengl_prj/glm/gtc/type_ptr.hpp>

#include </home/gustavo/Desktop/opengl_prj/shader.h>
#include </home/gustavo/Desktop/opengl_prj/camera.h>
#include <math.h>

#include <iostream>
#include <string>

#define pi 3.14159265359
#define epsilon 8.85418782e-12
#define numberOfSides 50
#define n_detectors 90


void angles_(float vec_x, float vec_y, float vec_z, float angles[]);
void ConeVertices(float vec_height, GLfloat allConeVertices[]);
void CylinderVertices(float vec_height, GLfloat allCylinderVertices[]);

//==================================================================================================================

int main(){

	int gridMax = 0, gridMin = 0;
	float dipx,dipy,dipz, px,py,pz;

	std::string input1, input2;
	std::ifstream file;
	file.open("input.txt");
	if(file.is_open())
	{
		getline(file, input1);
		getline(file, input1);
		std::istringstream ss(input1);
		getline(ss, input2, ':');
		getline(ss, input2, '\n');
		gridMax = atoi(input2.c_str()) / 2;
		gridMin = -atoi(input2.c_str()) / 2;

		getline(file, input1);
		getline(file, input1);
		std::istringstream sl(input1);
		getline(sl, input2, ':');
		getline(sl, input2, ',');
		dipx = atof(input2.c_str());
		getline(sl, input2, ',');
		dipy = atof(input2.c_str());
		getline(sl, input2, '\n');
		dipz = atof(input2.c_str());

		getline(file, input1);
		getline(file, input1);
		std::istringstream sn(input1);
		getline(sn, input2, ':');
		getline(sn, input2, ',');
		px = atof(input2.c_str());
		getline(sn, input2, ',');
		py = atof(input2.c_str());
		getline(sn, input2, '\n');
		pz = atof(input2.c_str());

		file.close();
	}
	else
	{
		std::cerr << "Failed to open input.txt file." << std::endl;
	}

    //Window Creation
    Window window;

    // Build and compile shader program
    Shader ourShader("shader.vs", "shader.fs");


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glm::vec3 positions[] = {

		glm::vec3(4.000,  0.000,   0.000),
		glm::vec3(-3.645,  0.000,   1.648),
		glm::vec3(2.641,  0.000,  -3.004),
		glm::vec3(-1.169,  0.000,   3.826),
		glm::vec3(-0.512,  0.000,  -3.967),
		glm::vec3(2.101,  0.000,   3.404),
		glm::vec3(-3.317,  0.000,  -2.235),
		glm::vec3(3.944,  0.000,   0.669),
		glm::vec3(-3.869,  0.000,   1.015),
		glm::vec3(3.107,  0.000,  -2.520),
		glm::vec3(-1.792,  0.000,   3.576),
		glm::vec3(0.159,  0.000,  -3.997),
		glm::vec3(1.502,  0.000,   3.707),
		glm::vec3(-2.896,  0.000,  -2.759),
		glm::vec3(3.776,  0.000,   1.320),
		glm::vec3(-3.984,  0.000,   0.353),
		glm::vec3(3.485,  0.000,  -1.964),
		glm::vec3(-2.365,  0.000,   3.226),
		glm::vec3(0.826,  0.000,  -3.914),
		glm::vec3(0.860,  0.000,   3.906),
		glm::vec3(-2.394,  0.000,  -3.205),
		glm::vec3(3.502,  0.000,   1.933),
		glm::vec3(-3.987,  0.000,  -0.318),
		glm::vec3(3.764,  0.000,  -1.353),
		glm::vec3(-2.872,  0.000,   2.784),
		glm::vec3(1.469,  0.000,  -3.720),
		glm::vec3(0.195,  0.000,   3.995),
		glm::vec3(-1.824,  0.000,  -3.560),
		glm::vec3(3.129,  0.000,   2.492),
		glm::vec3(-3.878,  0.000,  -0.981),
		glm::vec3(3.938,  0.000,  -0.704),
		glm::vec3(-3.297,  0.000,   2.264),
		glm::vec3(2.071,  0.000,  -3.422),
		glm::vec3(-0.477,  0.000,   3.971),
		glm::vec3(-1.202,  0.000,  -3.815),
		glm::vec3(2.668,  0.000,   2.981),
		glm::vec3(-3.659,  0.000,  -1.616),
		glm::vec3(4.000,  0.000,  -0.035),
		glm::vec3(-3.630,  0.000,   1.681),
		glm::vec3(2.615,  0.000,  -3.027),

		glm::vec3(0.718f,  0.8f,   2.913f),
		glm::vec3(1.395f,  0.8f,   2.656f),
		glm::vec3(1.990f,  0.8f,   2.245f),
		glm::vec3(2.469f,  0.8f,   1.704f),
		glm::vec3(2.805f,  0.8f,   1.063f),
		glm::vec3(2.978f,  0.8f,   0.360f),
		glm::vec3(2.978f,  0.8f,  -0.363f),
		glm::vec3(2.804f,  0.8f,  -1.065f),
		glm::vec3(2.468f,  0.8f,  -1.706f),
		glm::vec3(1.988f,  0.8f,  -2.247f),
		glm::vec3(1.392f,  0.8f,  -2.657f),
		glm::vec3(0.716f,  0.8f,  -2.913f),
		glm::vec3(-0.003f,  0.8f,  -3.000f),
		glm::vec3(-0.721f,  0.8f,  -2.912f),
		glm::vec3(-1.397f,  0.8f,  -2.655f),
		glm::vec3(-1.992f,  0.8f,  -2.243f),
		glm::vec3(-2.471f,  0.8f,  -1.701f),
		glm::vec3(-2.806f,  0.8f,  -1.060f),
		glm::vec3(-2.979f,  0.8f,  -0.358f),
		glm::vec3(-2.978f,  0.8f,   0.366f),
		glm::vec3(-2.804f,  0.8f,   1.068f),
		glm::vec3(-2.466f,  0.8f,   1.708f),
		glm::vec3(-1.986f,  0.8f,   2.249f),
		glm::vec3(-1.390f,  0.8f,   2.659f),
		glm::vec3(-0.713f,  0.8f,   2.914f),
		glm::vec3(0.005f,  0.8f,   3.000f),

		glm::vec3(0.765f,  1.5f,   1.848f),
		glm::vec3(1.414f,  1.5f,   1.414f),
		glm::vec3(1.848f,  1.5f,   0.765f),
		glm::vec3(2.000f,  1.5f,   0.000f),
		glm::vec3(1.848f,  1.5f,  -0.765f),
		glm::vec3(1.414f,  1.5f,  -1.414f),
		glm::vec3(0.765f,  1.5f,  -1.848f),
		glm::vec3(0.000f,  1.5f,  -2.000f),
		glm::vec3(-0.765f,  1.5f,  -1.848f),
		glm::vec3(-1.414f,  1.5f,  -1.414f),
		glm::vec3(-1.848f,  1.5f,  -0.765f),
		glm::vec3(-2.000f,  1.5f,   0.000f),
		glm::vec3(-1.848f,  1.5f,   0.765f),
		glm::vec3(-1.414f,  1.5f,   1.414f),
		glm::vec3(-0.765f,  1.5f,   1.848f),
		glm::vec3(0.000f,  1.5f,   2.000f),


		glm::vec3(0.707f,  2.0f,   0.707f),
		glm::vec3(1.000f,  2.0f,   0.000f),
		glm::vec3(0.707f,  2.0f,  -0.707f),
		glm::vec3(0.000f,  2.0f,  -1.000f),
		glm::vec3(-0.707f,  2.0f,  -0.707f),
		glm::vec3(-1.000f,  2.0f,   0.000f),
		glm::vec3(-0.707f,  2.0f,   0.707f),
		glm::vec3(0.000f,  2.0f,   1.000f),


            glm::vec3( dipx,  dipz,  dipy)
            //In first coordinate, +1 moves one house to the right at start, -1 moves one house to the left at start
            //In second coordinate, +1 moves one house up at start, -1 moves one house down at start
            //In third coordinate, +1 moves one house backwards at start, -1 moves one house frontwards at start
    };

    //Distances to origin (dipole)
    float distances[n_detectors];

    //This gets me the distances to the origin (i.e. the distances of each detector to the dipole)
    for(int i = 0; i < n_detectors; ++i)
    {
        distances[i] = sqrt( pow(positions[i].x-positions[n_detectors].x,2) + pow(positions[i].y-positions[n_detectors].y,2) + pow(positions[i].z-positions[n_detectors].z,2));
        //std::cout << (long double) distances[i] << std::endl;
    }



    //--------------------------------------GRID--------------------------------------------------

    int gridPoints = ( abs(gridMax) + abs(gridMin) ) * ( abs(gridMax) + abs(gridMin) ) ;

    //gridPoints += 2;

   /* GLfloat * gridVerticesX = new GLfloat[gridPoints];
    GLfloat * gridVerticesY = new GLfloat[gridPoints];
    GLfloat * gridVerticesZ = new GLfloat[gridPoints];
	GLfloat * allGridVertices = new GLfloat[gridPoints * 3];*/

	const int sgridPoints = 102;

	GLfloat gridVerticesX[gridPoints];
	GLfloat gridVerticesY[gridPoints];
	GLfloat gridVerticesZ[gridPoints];
	GLfloat allGridVertices[gridPoints * 3];

    for(int i = 0; i <= 2*gridMax; ++i){

        for(int j = 0; j < 2*gridMax; ++j){

            gridVerticesX[i*2*gridMax+j] = gridMin+i;
            if( j%2 == 0)
                gridVerticesY[i*2*gridMax+j] = gridMax;
            else
                gridVerticesY[i*2*gridMax+j] = gridMin;
            gridVerticesZ[i*2*gridMax+j] = 0;
        }
    }


    for ( int i = 0; i < sgridPoints; i++ ){

        allGridVertices[i * 3] = gridVerticesX[i];
        allGridVertices[( i * 3 ) + 1] = gridVerticesY[i];
        allGridVertices[( i * 3 ) + 2] = gridVerticesZ[i];
    }

    GLuint VBO3, VAO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	auto b = sizeof(allGridVertices);
	glBufferData(GL_ARRAY_BUFFER, b, allGridVertices, GL_STATIC_DRAW);
	


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //--------------------------------------------------------------------------------------------




    float vec_coor_array[3*(n_detectors + 1)];

    vec_coor_array[n_detectors * 3] = px;          //+1 sets vec direction to the left at start, -1 sets vec direction to the right at start
    vec_coor_array[(n_detectors * 3) + 1] = py;    //+1 sets vec direction backwards at start, -1 sets vec direction forwards at start
    vec_coor_array[(n_detectors * 3) + 2] = pz;    //+1 sets vec direction upwards at start,

    float max_inte = sqrt(vec_coor_array[n_detectors * 3]*vec_coor_array[n_detectors * 3] + vec_coor_array[(n_detectors * 3) + 1]*vec_coor_array[(n_detectors * 3) + 1] + vec_coor_array[(n_detectors * 3) + 2]*vec_coor_array[(n_detectors * 3) + 2]);
    float current_inte, var, field_k;

    for(int i = 0; i < n_detectors; ++i)
    {
        var = vec_coor_array[n_detectors * 3]*(-positions[i].x + positions[n_detectors].x) + vec_coor_array[(n_detectors * 3) + 1]*(positions[i].z - positions[n_detectors].z) + vec_coor_array[(n_detectors * 3) + 2]*(positions[i].y - positions[n_detectors].y);
        field_k = ( 1 / (4*epsilon*pi*distances[i]) ); //Constants 4*epsilon*pi removed


        //POISTION COORDINATES ADAPTED TO FIT VECTOR COORDINATE FORMAT, SEE NOTEBOOK FOR EXPLANATION
        vec_coor_array[i * 3] = field_k * ( ( var * (-positions[i].x + positions[n_detectors].x)  / (distances[i]*distances[i]) ) - vec_coor_array[(n_detectors * 3) +0] );
        vec_coor_array[(i * 3) + 1] = field_k * ( ( var * (positions[i].z - positions[n_detectors].z)  / (distances[i]*distances[i]) ) - vec_coor_array[(n_detectors * 3) + 1] );
        vec_coor_array[(i * 3) + 2] = field_k * ( ( var * (positions[i].y - positions[n_detectors].y)  / (distances[i]*distances[i]) ) - vec_coor_array[(n_detectors * 3) + 2] );

        //std::cout << (long double) vec_coor_array[i*3] << std::endl;


        //Get maximum intensity
        current_inte = sqrt(vec_coor_array[i * 3]*vec_coor_array[i * 3] + vec_coor_array[(i * 3) + 1]*vec_coor_array[(i * 3) + 1] + vec_coor_array[(i * 3) + 2]*vec_coor_array[(i * 3) + 2]);
        if(current_inte > max_inte)
            max_inte = current_inte;
    }





    ourShader.use();


    // rendering loop
    while (!window.windowShouldClose()){

        // input
        window.processInput();

        // render
        window.render();

        // activate shader
        ourShader.use();
        glm::mat4 center;
        center = glm::translate(center, glm::vec3( 0.0f,  0.0f,  0.0f));
        ourShader.setMat4("pos", center);
        glm::mat4 main_rotation;
        main_rotation = glm::rotate(main_rotation, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("main_rotation", main_rotation);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        glm::mat4 model;
        ourShader.setMat4("model", model);


	float timeValue = glfwGetTime();
	float redValue = sin(timeValue*10);
    	float greenValue = sin(timeValue);
	float blueValue = cos(timeValue*10);
	ourShader.setVec4("dipole_color", glm::vec4( redValue, greenValue, blueValue, 1.0f));
	ourShader.setBool("dipole", false);

        //------------------------------------GRID----------------------------------------------------
        ourShader.setVec4("grid_color", glm::vec4( 0.0f, 0.5f, 0.7f, 1.0f));
        ourShader.setBool("grid", true);

        glBindVertexArray(VAO3);
        glDrawArrays(GL_LINES, 0, gridPoints);

        glm::mat4 model3;
        model3 = glm::rotate(model3, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ourShader.setMat4("model", model3);

        glDrawArrays(GL_LINES, 0, gridPoints);
	
	ourShader.setBool("grid", false);
        //--------------------------------------------------------------------------------------------
	

        for(int i = 0; i < n_detectors + 1 ; ++i){

		float x_coor = vec_coor_array[i * 3];
            	float y_coor = vec_coor_array[(i * 3) + 1];
            	float z_coor = vec_coor_array[(i * 3) + 2];
	

            float vec_height = sqrt(x_coor*x_coor + y_coor*y_coor + z_coor*z_coor);    //THIS IS THE VECTOR'S INTENSITY

           
	    if(i != n_detectors)	
	    	vec_height = vec_height / max_inte;
	    else
		ourShader.setBool("dipole", true);
		

            ourShader.setFloat("max_inte", 1.0f);
            ourShader.setFloat("intensity", vec_height);
            
            float angles[2] = {0.0f, 0.0f};
            angles_(x_coor, y_coor, z_coor, angles);

	    
            //------------------------------------CONE----------------------------------------------------

            GLfloat allConeVertices[( numberOfSides + 2 ) * 3];
            ConeVertices(vec_height, allConeVertices);  //MAYBE DIVIDE vec_height HERE AND IN CYLINDER BY gridMax, TO NORMALIZE VIEW

            unsigned int VBO, VAO, EBO;

            glGenBuffers(1, &EBO);
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(allConeVertices), allConeVertices, GL_STATIC_DRAW);


            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //--------------------------------------------------------------------------------------------



            //---------------------------------CYLINDER---------------------------------------------------

            GLfloat allCylinderVertices[( numberOfSides ) * 3];
            CylinderVertices(vec_height, allCylinderVertices);


            unsigned int VAO2, VBO2;

            glGenBuffers(1, &VBO2);

            glBindBuffer(GL_ARRAY_BUFFER, VBO2);

            glGenVertexArrays(1, &VAO2);

            glBindVertexArray(VAO2);

            glBufferData(GL_ARRAY_BUFFER, sizeof(allCylinderVertices), allCylinderVertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //--------------------------------------------------------------------------------------------


                glm::mat4 mm;
                glm::mat4 pos;

                /*
                 * Since OpenGl reads the rotations in the backwards order that they are written in, then
                 * we need to write them reversed as well in order for them to work. Since the vectors are
                 * originally being drawn along the z axis (rotation around the z axis meaningless), then
                 * we need to first rotate them along the x or y axis, for a z axis rotation to have meaning
                 * Therefore, reverse that, and we do z axis first, and then x or y axis rotation
                 */
                glm::mat4 model2;

                model2 = glm::rotate(model2, angles[1], glm::vec3(0.0f, 1.0f, 0.0f));
                model2 = glm::rotate(model2, angles[0], glm::vec3(1.0f, 0.0f, 0.0f));

                //ROTATIONS AROUND X AND Y AXIS (TO GET THE VECTOR I WANT BASED ON (0,0,1))
                mm = glm::translate(model2, glm::vec3(0.0f, 0.0f, 0.0f));
                ourShader.setMat4("model", mm);


                pos = glm::translate(pos, positions[i]);
                ourShader.setMat4("pos", pos);


                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfSides);

                glBindVertexArray(VAO2);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, numberOfSides);


		//optional: de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO2);
		glDeleteBuffers(1, &VBO2);

        }

	
        // update (buffers)
        window.swapNPoll();
    }



    // optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);


    return 0;
}


//==================================================================================================================

void angles_(float vec_x, float vec_y, float vec_z, float angles[])
{
    float vec_height = sqrt(vec_x*vec_x + vec_y*vec_y + vec_z*vec_z);

    if(vec_z >= 0)
    {
        if(vec_x == 0 && vec_z == 0)
        {
            if(vec_y > 0)
                angles[0] = glm::radians(90.0f);
            else
                angles[0] = glm::radians(-90.0f);
        }
        else
        {
            angles[0] = asin(vec_y/vec_height);
            angles[1] = atan(vec_x/vec_z);
        }
    }
    else
    {
        if(vec_x == 0 && vec_y == 0)
        {
            angles[0] = glm::radians(180.0f);
        }
        else
        {
            angles[1] = atan(vec_x/vec_z);
            angles[0] = pi - asin(vec_y/vec_height);
        }
    }

}

//==================================================================================================================

void ConeVertices(float vec_height, GLfloat allConeVertices[])
{
    //GLfloat z = 0.1;
    GLfloat radius = 0.05;

   const int numberOfVertices = numberOfSides;

    GLfloat twicePi = 2.0f * pi;

    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    circleVerticesX[0] = 0.0f;
    circleVerticesY[0] = 0.0f;
    circleVerticesZ[0] = -vec_height;



    for ( int i = 1; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = ( radius * cos( i * twicePi / (numberOfVertices-2) ) );
        circleVerticesY[i] = ( radius * sin( i * twicePi / (numberOfVertices-2) ) );
        if(vec_height == 0)
            circleVerticesZ[i] = 0;
        else
            circleVerticesZ[i] = -vec_height+0.1;
    }



    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allConeVertices[i * 3] = circleVerticesX[i];
        allConeVertices[( i * 3 ) + 1] = circleVerticesY[i];
        allConeVertices[( i * 3 ) + 2] = circleVerticesZ[i];
    }
}

//==================================================================================================================

void CylinderVertices(float vec_height, GLfloat allCylinderVertices[])
{
    GLfloat cylinderVerticesX[numberOfSides];
    GLfloat cylinderVerticesY[numberOfSides];
    GLfloat cylinderVerticesZ[numberOfSides];


    //Cylinder with y axis up
    GLfloat cylinder_radius = 0.01f;


    for (int i = 0; i < numberOfSides ; ++i)
    {
        GLfloat u = i / ((GLfloat)numberOfSides-2);

        //Where the cylinder is in the x and z positions (3D space)
        cylinderVerticesX[i] = cylinder_radius*cos(2*pi*u);
        cylinderVerticesY[i] = cylinder_radius*sin(2*pi*u);
        if(vec_height == 0)
            cylinderVerticesZ[i] = 1.0 * (i % 2 == 0 ? 0.0 : 0.0);
        else
            cylinderVerticesZ[i] = 1.0 * (i % 2 == 0 ? 0.0 : -vec_height+0.1);
    }


    for ( int i = 0; i < numberOfSides; i++ )
    {
        allCylinderVertices[i * 3] = cylinderVerticesX[i];
        allCylinderVertices[( i * 3 ) + 1] = cylinderVerticesY[i];
        allCylinderVertices[( i * 3 ) + 2] = cylinderVerticesZ[i];
    }

}

//==================================================================================================================
