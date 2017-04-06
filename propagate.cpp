// implement the propagate application here

#include "heap_priority_queue.h"
#include "image.h"
#include <iostream>

// Class with defined > and < operators
class pixelComp {
private:
	int pixelX;
	int pixelY;
	int RSpeed;
public:
	pixelComp() {
		pixelX = 0;
		pixelY = 0;
		RSpeed = 0;
	}

	pixelComp(int xInput, int yInput, int redSpeed) {
		pixelX = xInput;
		pixelY = yInput;
		RSpeed = redSpeed;
	}

	int getPixelX() {
		return pixelX;
	}

	int getPixelY() {
		return pixelY;
	}

	friend bool operator <(const pixelComp& a, const pixelComp& d) {
		if (a.RSpeed < d.RSpeed) return true;
		return false;
	}

	friend bool operator >(const pixelComp& a, const pixelComp& d) {
		if (a.RSpeed < d.RSpeed) return true;
		return false;
	}

};

int main(int argc, char *argv[])
{

	if (argc != 5) {
		std::cout << "Usage: propagate"
			<< "<initial_filename> <speed_filename> <output_filename> <Timesteps>\n"
			<< std::endl;
		return EXIT_FAILURE;
	}
	
	try {

		bool toStore = false;

		int T = atoi(argv[4]);
		if (T <= 0) {
			std::cerr << "Invalid input T" << std::endl;
			return EXIT_FAILURE;
		}

		HeapPriorityQueue<pixelComp> mainList;

		Image<Pixel> boundary = readFromFile(argv[1]);
		Image<Pixel> speed = readFromFile(argv[2]);

		Image<Pixel> output = boundary;

		if (boundary.width() != speed.width() || boundary.height() != speed.height()) {
			std::cerr << "Inial and Speed images are not the same size" << std::endl;
			return EXIT_FAILURE;
		}

		for (std::size_t i = 0; i < boundary.width(); i++) {
			for (std::size_t j = 0; j < boundary.height(); j++) {
				toStore = false;

				if (!((boundary(i, j).red == 0 && boundary(i, j).green == 0 && boundary(i, j).blue == 0) || (boundary(i, j).red == 255 && boundary(i, j).green == 255 && boundary(i, j).blue == 255))) {
					std::cerr << "One or more pixels in the initial image is not white or black" << std::endl;
					return EXIT_FAILURE;
				}

				// if pixel is black
				if (boundary(i, j).red == 0) {
					if (i != 0) {
						if (boundary(i - 1, j).red > 0) {
							toStore = true;
						}
					}
					if (i != boundary.width() - 1) {
						if (boundary(i + 1, j).red > 0) {
							toStore = true;
						}
					}
					if (j != 0) {
						if (boundary(i, j - 1).red > 0) {
							toStore = true;
						}
					}
					if (j != boundary.height() - 1) {
						if (boundary(i, j + 1).red > 0) {
							toStore = true;
						}
					}
					if (toStore == true) {
						mainList.add(pixelComp(i, j, speed(i, j).red));
						output(i, j).red = 0;
						output(i, j).green = 0;
						output(i, j).blue = 0;
						toStore = false;
					}
				} // end if pixel is black
			} // end inside for loop
		} // end outside for loop

		// We now have the boundary pixels in the queue

		pixelComp toAdd = mainList.peek();
		mainList.remove();

		for (int t = 0; t < T; t++) {
			output(toAdd.getPixelX(), toAdd.getPixelY()).red = 0;
			output(toAdd.getPixelX(), toAdd.getPixelY()).green = 0;
			output(toAdd.getPixelX(), toAdd.getPixelY()).blue = 0;

			// left right up down
			if (toAdd.getPixelX() != 0) {
				if (output(toAdd.getPixelX() - 1, toAdd.getPixelY()).red != 0) mainList.add(pixelComp(toAdd.getPixelX() - 1, toAdd.getPixelY(), speed(toAdd.getPixelX() - 1, toAdd.getPixelY()).red));
			}
			if (toAdd.getPixelX() != boundary.width() - 1) {
				if (output(toAdd.getPixelX() + 1, toAdd.getPixelY()).red != 0) mainList.add(pixelComp(toAdd.getPixelX() + 1, toAdd.getPixelY(), speed(toAdd.getPixelX() + 1, toAdd.getPixelY()).red));
			}
			if (toAdd.getPixelY() != 0) {
				if (output(toAdd.getPixelX(), toAdd.getPixelY() - 1).red != 0) mainList.add(pixelComp(toAdd.getPixelX(), toAdd.getPixelY() - 1, speed(toAdd.getPixelX(), toAdd.getPixelY() - 1).red));
			}
			if (toAdd.getPixelY() != boundary.height() - 1) {
				if (output(toAdd.getPixelX(), toAdd.getPixelY() + 1).red != 0) mainList.add(pixelComp(toAdd.getPixelX(), toAdd.getPixelY() + 1, speed(toAdd.getPixelX(), toAdd.getPixelY() + 1).red));
			}

			toAdd = mainList.peek();
			mainList.remove();
			if (mainList.isEmpty()) break;
		}
		writeToFile(output, argv[3]);
	}
	catch (std::runtime_error) {
		std::cerr << "One or more input files were invalid" << std::endl;
		return EXIT_FAILURE;
	}

	
	return EXIT_SUCCESS;
}
