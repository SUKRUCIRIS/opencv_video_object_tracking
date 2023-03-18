#include <opencv2/opencv.hpp>

//I used opencv 4.7.0
int main() {
	cv::VideoCapture video("input_video.mp4");
	if (!video.isOpened()) {
		return -1;
	}

	cv::Mat frame;

	cv::Ptr<cv::Tracker> tracker = cv::TrackerMIL::create();
	video.read(frame);
	cv::Rect trackingbox = cv::selectROI(frame, false);
	tracker->init(frame, trackingbox);

	int framewidth = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
	int frameheight = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter output("output_video.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 30, cv::Size(framewidth, frameheight));

	while (video.read(frame)) {
		tracker->update(frame, trackingbox);
		cv::rectangle(frame, trackingbox, cv::Scalar(0, 0, 255,255));
		cv::imshow("Tracking", frame);
		output.write(frame);
		cv::waitKey(10);
	}
	
	output.release();
	video.release();
	cv::destroyAllWindows();
	return 0;
}