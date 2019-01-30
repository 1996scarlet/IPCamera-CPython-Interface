#include "../sdk/include/CXMCamera.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    XMIPCamera cp = XMIPCamera("10.41.0.208", 34567, "admin", "");
    cp.login();
    cp.open();

    sleep(2);

    for (auto i = 0; i < 500; i++)
    {
        imshow("display", cp.get_current_frame_mat());
        waitKey(1);
    }

    cp.close();
    return 0;
}
