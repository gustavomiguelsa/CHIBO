//==========================================================================================
//Window construction class 
//Created by Gustavo Assunção
//==========================================================================================

#ifndef GRID_H
#define GRID_H

//-----------------------------------------------------------------------------------------

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SHADER/shader.h>
#include <WINDOW/window.h>


#include <iostream>


//-----------------------------------------------------------------------------------------

class Grid{

public:
	
	unsigned int VBO;
        unsigned int VAO;
	int gridPoints;

        Grid(){

            gridMax = 5;
            gridMin = -5;
            gridPoints = ( abs(gridMax) + abs(gridMin) ) * ( abs(gridMax) + abs(gridMin) ) ;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
        }

        void generateGrid(){

    		GLfloat gridVerticesX[gridPoints];
    		GLfloat gridVerticesY[gridPoints];
    		GLfloat gridVerticesZ[gridPoints];

    		GLfloat allGridVertices[(gridPoints) * 3];

    		for(int i = 0; i < 2*gridMax; ++i){

        		for(int j = 0; j < 2*gridMax; ++j){

            			gridVerticesX[i*2*gridMax+j] = gridMin+j;
            			gridVerticesY[i*2*gridMax+j] = gridMin+i;
            			gridVerticesZ[i*2*gridMax+j] = 0;
        		}
    		}


    		for ( int i = 0; i < gridPoints; i++ ){

        		allGridVertices[i * 3] = gridVerticesX[i];
        		allGridVertices[( i * 3 ) + 1] = gridVerticesY[i];
        		allGridVertices[( i * 3 ) + 2] = gridVerticesZ[i];
    		}

    		glBufferData(GL_ARRAY_BUFFER, sizeof(allGridVertices), allGridVertices, GL_STATIC_DRAW);

    		// position attribute
    		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    		glEnableVertexAttribArray(0);
	}

	void drawGrid(){


		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        	ourShader.setMat4("projection", projection);

       		glm::mat4 view = camera.GetViewMatrix();
        	ourShader.setMat4("view", view);


	        glBindVertexArray(VAO);
	
	        glm::mat4 model;
	
	
	        //model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
	        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	        ourShader.setMat4("model", model);


	        glDrawArrays(GL_LINES, 0, gridPoints);	
	}

private:
    
        int gridMax;
        int gridMin;

};

#endif

//==========================================================================================
