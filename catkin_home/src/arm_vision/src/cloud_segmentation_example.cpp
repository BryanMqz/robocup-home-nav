#include <SegmentationNode/SegmentationNode.h>

//////////////////////////////////////
/////////////////////////////////////

int main(int argc, char* argv[]) {
    // Initialize ROS
    ros::init(argc, argv, "arm_vision");
    ros::NodeHandle nh("~");
    std::string camera_selection = "";

    nh.getParam("camera_selection", camera_selection);
    ROS_INFO("Got selection : %s", camera_selection.c_str());

    if(camera_selection.compare("intel") != 0 && camera_selection.compare("kinect") != 0)
    {
        ROS_ERROR("Not camera selected");
        return 0;
        
    }
    segmentation segs(nh, camera_selection);


    // Spin
    ros::spin();
}
