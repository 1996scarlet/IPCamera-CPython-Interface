#include "../sdk/include/CHKCamera.h"
#include <unistd.h>
using namespace std;
int main()
{
    HKIPCamera *hkcp = new HKIPCamera("10.41.0.236", 8000, "admin", "humanmotion01");

    cout << *hkcp << endl;

    // for (auto i = 0; i < 1000; i++)
    // {
    //     long cus = (long)hkcp;

    //     HKIPCamera *cp = (HKIPCamera *)cus;
    //     cout << *cp << endl;
    // }

    hkcp->start();
    sleep(1);

    for (auto i = 0; i < 50; i++)
    {
        cv::imshow("display", hkcp->current());
        cv::waitKey(1);
    }

    hkcp->stop();
    delete hkcp;
}
