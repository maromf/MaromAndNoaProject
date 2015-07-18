/*
 * LoadManager.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: colman
 */

#include "LoadManager.h"

	LoadManager::LoadManager()
	{
		IMAGE_PIXLE_COLUMNS = 0;
		IMAGE_PIXLE_ROWS = 0;
	}

	unsigned LoadManager::getImagePixleRows()
	{
		return IMAGE_PIXLE_ROWS;
	}

	unsigned LoadManager::getImagePixleColumns()
	{
		return IMAGE_PIXLE_COLUMNS;
	}

	//Example 1
	//Decode from disk to raw pixels with a single function call
	void LoadManager::loadImage(const char* filename)
	{
	  //decode
		unsigned error = lodepng::decode(image, IMAGE_PIXLE_COLUMNS, IMAGE_PIXLE_ROWS, filename);

	  //if there's an error, display it
	  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
	}

	//Example 1
	//Encode from raw pixels to disk with a single function call
	//The image argument has width * height RGBA pixels or width * height * 4 bytes
	void LoadManager::saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
	{
	  //Encode the image
	  unsigned error = lodepng::encode(filename, image, IMAGE_PIXLE_COLUMNS, IMAGE_PIXLE_ROWS);

	  //if there's an error, display it
	  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
	}

	/*
	 *
	 */
	std::vector<std::vector<int> > LoadManager::generateImgGrid(const char *pngFile)
	{
		loadImage(pngFile);
		int freeCellInt = FREE_CELL;
		int occupiedCellInt = OCCUPIED_CELL;
		std::vector<std::vector<int> > grid(IMAGE_PIXLE_ROWS, std::vector<int>(IMAGE_PIXLE_COLUMNS));
		for(unsigned i = 0; i < IMAGE_PIXLE_ROWS * IMAGE_PIXLE_COLUMNS * PIXEL_LENGHT; i += PIXEL_LENGHT)
		{
			grid[(i / 4) / IMAGE_PIXLE_COLUMNS][(i / 4) % IMAGE_PIXLE_COLUMNS] =
					((image[i] != 255) || (image[i + 1] != 255) || (image[i + 2] != 255) || (image[i + 3] != 255))
					?(freeCellInt):(occupiedCellInt);
		}

		return grid;
	}

	//TODO: fix
	int LoadManager::load()
	{
		const char* filename = "hospital_section.png";
		loadImage(filename);

		cout << "width: " << IMAGE_PIXLE_COLUMNS << ", height: " << IMAGE_PIXLE_ROWS << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << (int)image[i] << " ";
		}
		cout << endl;

		//  Change the first line to black
		for (unsigned int i = 0; i < IMAGE_PIXLE_COLUMNS * 4 * 5; i+=4)
		{
			image[i] = 0;
			image[i + 1] = 0;
			image[i + 2] = 0;
			image[i + 3] = 255;
		}

		const char* newfile = "hospital_section2.png";
		saveImage(newfile, image, IMAGE_PIXLE_COLUMNS, IMAGE_PIXLE_ROWS);

		return 0;
	}

	LoadManager::~LoadManager()
	{
	}



