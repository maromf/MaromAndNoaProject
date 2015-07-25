/**
 * LoadManager.h
 *
 *  Purpose: Manage the access to the image loading and saving model.
 *

 *  Created on: Jun 20, 2015
 *  @author:    MaromF
 *  @version:   1.0
 */
#ifndef LOADMANAGER_H_
#define LOADMANAGER_H_

#include "lodepng.h"
#include <iostream>
#include "../Framework/Grid.h"
#include "../ConfigManager.h"

using namespace std;

class LoadManager {

	private:
		std::vector<unsigned char> image; //the raw pixels
		unsigned IMAGE_PIXLE_ROWS;
		unsigned IMAGE_PIXLE_COLUMNS;
		static const unsigned PIXEL_LENGHT = 4; //4 Bytes per pixel
		static const int FREE_CELL = 0;
		static const int OCCUPIED_CELL = 1;
		static const int UNKNOWN_CELL = 2;
		static const int PATH_CELL = 3;
		static const int WAY_POINT_CELL = 4;
		static const int START_CELL = 5;
		static const int END_CELL = 6;

	public:
		LoadManager();           // Ctor
		virtual ~LoadManager();  // Dtor
		unsigned getImagePixleRows();
		unsigned getImagePixleColumns();
		void loadImage(const char* filename);
		void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
		int load();

		/**
		    This method  responsible of generating an vectors Grid out of a given path of image.
		    The method gets the image file , reads its and transforms it into grid.
		    The method build the grid according to the given cell resolution (CM) from the configuration model.

		    @param pngFile - The image file path.
		    @return The generated grid (vector<vector<int>>).
		*/
		Grid* generateImgGrid(const char* pngFile);

		void SaveImgFromGrid(Grid* grid, const char *filename);
};



#endif /* LOADMANAGER_H_ */
