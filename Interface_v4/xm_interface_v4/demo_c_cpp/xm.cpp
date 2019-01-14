#include "../sdk/include/CXMCamera.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace cv;
int main()
{
    XMIPCamera cp = XMIPCamera("10.41.0.211", 34567, "admin", "");

    cp.login();
    cp.open();

    sleep(2);

    // // cp.start_real_play(200);
    int i = 0;
    while (i++ < 5000)
    {
        // cout << "10.41.0.211" << endl;
        imshow("display", cp.get_current_frame_mat());
        waitKey(1);
    }

    cp.close();
    return 0;
}

 
