#include "ocr.h"
#include <args-parser/all.hpp>

using namespace Args;

int main(int argc, char **argv) {
    try {
        CmdLine cmd(argc, argv);

        cmd.addArgWithFlagAndName('i', "input_path", true, true, "Input image path",
                                  "Input image path", "", "path")
                .addArgWithFlagAndName('m', "models_path", true, false, "Models store folder path",
                                       "Models store folder path", "../models", "path")
                .addArgWithFlagAndName('l', "resize_length", true, false, "Resize image length",
                                       "Resize image to specified length, eg. 640", "", "length")
                .addHelp(true, argv[0], "A lightweight Chinese OCR application.");

        cmd.parse();

        std::string image_path = cmd.value("-i");
        int long_size = 0;
        if (cmd.isDefined("-l")) {
            long_size = std::stoi(cmd.value("-l"));
        }
        std::string model_path = "../models";
        if (cmd.isDefined("-m")) {
            model_path = cmd.value("-m");
        }

        cv::Mat im_bgr = cv::imread(image_path, 1);
        if (im_bgr.empty()) {
            fprintf(stderr, "cv::imread %s failed\n", image_path.c_str());
            return -1;
        }

        OCR *ocr_engine = new OCR(model_path);

        std::cout << "start detect" << std::endl;
        ocr_engine->detect(im_bgr, long_size);

        delete ocr_engine;
    }
    catch (const HelpHasBeenPrintedException &) {
        return 0;
    }
    catch (const BaseException &x) {
        outStream() << x.desc() << "\n";
        return -1;
    }

    return 0;
}
