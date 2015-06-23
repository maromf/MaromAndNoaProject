/*
 * LoadManager.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Marom
 */

#ifndef LOADMANAGER_H_
#define LOADMANAGER_H_

#include "lodepng.h"
#include <iostream>
#include "../Utils.h"
#include "../ConfigManager.h"

using namespace std;

namespace MNProj{
	class LoadManager {
	private:
		std::vector<unsigned char> image; //the raw pixels
		unsigned IMAGE_PIXLE_ROWS;
		unsigned IMAGE_PIXLE_COLUMNS;
		const unsigned PIXEL_LENGHT = 4; //4 Bytes per pixel

	public:
		LoadManager();
		unsigned getImagePixleRows();
		unsigned getImagePixleColumns();
		void loadImage(const char* filename);
		void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
		int load();
		std::vector< std::vector<int> > generateImgGrid(const char* pngFile);
		virtual ~LoadManager();
	};
}


#endif /* LOADMANAGER_H_ */
