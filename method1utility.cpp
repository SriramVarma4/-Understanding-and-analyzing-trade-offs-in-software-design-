#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/core/utility.hpp>


using namespace std;
using namespace cv;

int main(int argc,char* argv[]){
    // Display image
    //Mat im_out = Mat(900,1300,0);
	int X;
	//float y;
    float err =0.0;
	float ms =0.0;
	ofstream table("utility1.txt");
	table<< "x,UTILITY\n";

	for (X=4;X<=15;X=X+1){
	
	VideoCapture cap(argv[1]);
	if (!cap.isOpened()){
		cout<<"\nerror reading the video\n";
		return 0;
	}  

	Mat imgdiff;
	//Mat back_image = imread("empty.png", IMREAD_GRAYSCALE);
    Mat back_image = imread("empty.png");
    if ( back_image.empty() ) 
    { 
        cout << "Error loading the image" << endl;
        return -1; 
    }
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(925, 220));//left up
    pts_src.push_back(Point2f(225, 1004));//left bottom
    pts_src.push_back(Point2f(1552, 1004));//right bottom
    pts_src.push_back(Point2f(1295, 220));//right up

    vector<Point2f> pts_dst;
    pts_dst.push_back(Point2f(0, 0));//left up
    pts_dst.push_back(Point2f(0, 800));//left bottom
    pts_dst.push_back(Point2f(400, 800));//right bottom
    pts_dst.push_back(Point2f(400, 0));//right up

	Mat h = findHomography(pts_src, pts_dst);
    //warped image
    Mat warp_back;
    Mat warp_backb;
    // Warp source image to destination based on homography
    warpPerspective(back_image, warp_back, h, back_image.size());
    warpPerspective(back_image, warp_backb, h, back_image.size());

	Mat back_crop = warp_back(Rect(0, 0, 400, 800));
    Mat back_cropb = warp_backb(Rect(0, 0, 400, 800));
	//imshow("bc", back_crop);
	int fm_count = 1;
	int rows = back_crop.rows;
	int cols = back_crop.cols;
    int rowsb = back_cropb.rows;
	int colsb = back_cropb.cols;


	Mat f_crop;
    Mat f_cropb;
	cout<<"executing\n";
	//new
	Ptr<BackgroundSubtractor> pBackSub;
    Ptr<BackgroundSubtractor> pBackSubb;
	pBackSub = createBackgroundSubtractorMOG2();
    pBackSubb = createBackgroundSubtractorMOG2();  
	Mat fgmask;
    Mat fgmaskb;
	Mat frame;
    Mat frameb;
	int qd = 0; //measure of queue density
	int dd = 0; //measure of dynamic density
    int qdb = 0;
    int ddb= 0;
	

	while (true){
		bool next = cap.read(frame);
			if (next==false){
				cout<<"end of video\n";
				break;
			}
        frameb = frame.clone();
		if (fm_count%X==1){
			//cout<<"yes"<<endl;
			//warped image
    		Mat warp_frame;
            
    		warpPerspective(frame, warp_frame, h, back_image.size());
            //warpPerspective(frame, warp_frameb, h, back_image.size());
            
    		// Display image
			f_crop = warp_frame(Rect(0, 0, 400, 800));
			
			pBackSub->apply(f_crop, fgmask, .04);
			imshow("fgmask", fgmask);

			if (fm_count >=5){
	    	for(int y=0; y<rows; y++)
			{
    	    for(int x=0; x<cols; x++)
        	{
	    	    Vec3b & fc = f_crop.at<Vec3b>(Point(x,y));
    		    Vec3b & bc = back_crop.at<Vec3b>(Point(x,y));
    	    	/*int c1,c2,c0;
    		    c0 = abs(fc[0]-bc[0]);
	    	    c1 = abs(fc[1] - bc[1]);
    		    c2 = abs(fc[2]-bc[2]);*/
        		if( abs(fc[2]-bc[2])> 60 || abs(fc[1]-bc[1]) > 60 || abs(fc[0]-bc[0]) > 60)
        		{
	            	/*fc[0] = 230;
    	        	fc[1] = 230;
        	    	fc[2] = 230;*/
        	    	qd++;
    	    	}
        		Vec3b & dc = fgmask.at<Vec3b>(Point(x,y));
        		if (dc[0] > 0){
        			dd++;
        		}
				
	    	}
    		}

			}
			//imshow("cropped", f_crop);
  		}
        if ( fm_count%5 == 1){
            Mat warp_frameb;
            warpPerspective(frameb, warp_frameb, h, back_image.size());
            f_cropb = warp_frameb(Rect(0, 0, 400, 800));

			pBackSubb->apply(f_cropb, fgmaskb, .04);
			imshow("fgmaskb", fgmaskb);

            if (fm_count>=5){
            for(int y=0; y<rowsb; y++)
			{
    	    for(int x=0; x<colsb; x++)
        	{
	    	    Vec3b & fcb = f_cropb.at<Vec3b>(Point(x,y));
    		    Vec3b & bcb = back_cropb.at<Vec3b>(Point(x,y));
    	    	/*int c1,c2,c0;
    		    c0 = abs(fc[0]-bc[0]);
	    	    c1 = abs(fc[1] - bc[1]);
    		    c2 = abs(fc[2]-bc[2]);*/
        		if( abs(fcb[2]-bcb[2])> 60 || abs(fcb[1]-bcb[1]) > 60 || abs(fcb[0]-bcb[0]) > 60)
        		{
	            	/*fc[0] = 230;
    	        	fc[1] = 230;
        	    	fc[2] = 230;*/
        	    	qdb++;
    	    	}
        		Vec3b & dcb = fgmaskb.at<Vec3b>(Point(x,y));
        		if (dcb[0] > 0){
        			ddb++;
        		}
				
	    	}
    		}

            }
        }
        if (waitKey(10) == 27){
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            table.close();
            return 0;
        }
        else if(fm_count>5 && fm_count%5 == 3 ){
            //cout << fm_count  << ',' << qd/(320000.0) << ',' << dd/(320000.0) << endl;
            //cout << fm_count  << ',' << qdb/(320000.0) << ',' << ddb/(320000.0) << endl;
            err =pow(((qd/(320000.0))- (qdb/(320000.0))),2);
            if (err != 0){
            err = err/(pow(((qdb/320000.0)),2));
            }
			ms = ms + err; 
  		}
		else if(fm_count%X==0 && fm_count%5==0){
			qd=0; dd=0;	
			qdb=0; ddb=0; err=0;
		}
		if(fm_count%X==0){
			qd=0; dd=0;	
		}
		else if(fm_count%5==0){
			qdb=0; ddb=0; err=0;
		} 
  		fm_count++;		
	}
    //cout<<ms<<endl;
    int total = (int) fm_count/5;
    ms = ms/total;
	ms=sqrt(ms);
    cout<<ms<<endl;
	table << X << ',' << 100-ms*100 << endl;
	cout<<"done\n";
	}
	table.close();
}	
