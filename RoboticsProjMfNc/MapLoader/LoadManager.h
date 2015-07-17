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
#include "../Utils.h"
#include "../ConfigManager.h"

using namespace std;

namespace MNProj {
	class LoadManager {
	private:
		std::vector<unsigned char> image; //the raw pixels
		unsigned IMAGE_PIXLE_ROWS;
		unsigned IMAGE_PIXLE_COLUMNS;
		static const unsigned PIXEL_LENGHT = 4; //4 Bytes per pixel

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
		std::vector< std::vector<int> > generateImgGrid(const char* pngFile);
	};
}


#endif /* LOADMANAGER_H_ */
