#include "../sdk/include/CHKCamera.h"
#include <unistd.h>
using namespace std;
int main()
{
    HKIPCamera *hkcp = new HKIPCamera("10.41.0.236", 8000, "admin", "humanmotion01");
    hkcp->start();
    sleep(1);

    for (auto i = 0; i < 50; i++)
    {
        cv::imshow("display", hkcp->current());
        cv::waitKey(1);
    }

    hkcp->stop();
    delete (hkcp);
}
