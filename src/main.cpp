#include <xilinx/ai/facequality.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <boost/filesystem.hpp>
#include <thread>

using namespace std;

void ListImages(
    std::string const &path,
    std::vector<std::pair<std::string, std::string>>  &images
)
{
    int num_images = 0;
    for ( boost::filesystem::recursive_directory_iterator end, dir(path);
        dir != end; ++dir )
    {
        std::string file_name =  dir->path().filename().string();
        std::string full_path =  dir->path().string();
        std::string ext = file_name.substr(file_name.find_last_of(".") + 1);
        if ((ext == "JPEG") || (ext == "jpeg") || (ext == "JPG") ||
            (ext == "jpg") || (ext == "PNG") || (ext == "png"))
        {
            images.push_back(std::make_pair(file_name, full_path));
			std::cout << num_images << " pushed to the queue" << std::endl;
			num_images++;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Error: Please provide the following two arguments to the executable: "<< std::endl << "<input_root_dir> <#_of_threads>" <<
        std::endl;
        return 0;
    }

    std::vector<std::pair<std::string, std::string>>  images;
    std::string path = argv[1];
    ListImages(path, images);

    int gThreads = atoi(argv[2]);
    std::vector<std::thread> threads(gThreads);
    std::vector<std::unique_ptr<xilinx::ai::FaceQuality>> qualityps(gThreads);
    for (int i = 0; i < gThreads; i++) {
      qualityps[i] = xilinx::ai::FaceQuality::create(xilinx::ai::FACE_QUALITY_3C);
    }

    for (int i = 0; i < gThreads; i++) {
        auto& qualityp = qualityps[i];
        threads[i] = std::thread([&](){
            while(1) {
                for (auto im:images)
                {

                    cv::Mat img = cv::imread(im.second);
                    auto result = qualityp->run(img);
                    std::cout << result.value << std::endl;
                }
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
