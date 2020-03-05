/*
This program detects image features using SIFT keypoints. For more info,
refer to:

Lowe, D. Distinctive image features from scale-invariant keypoints.
International Journal of Computer Vision, 60, 2 (2004), pp.91--110.

Copyright (C) 2006-2012  Rob Hess <rob@iqengines.com>

Note: The SIFT algorithm is patented in the United States and cannot be
used in commercial products without a license from the University of
British Columbia.  For more information, refer to the file LICENSE.ubc
that accompanied this distribution.

Version: 1.1.2-20100521
*/

#include "sift.h"
#include "imgfeatures.h"
#include "utils.h"

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

//#include <unistd.h> //unix 标准头文件

#define OPTIONS ":o:m:i:s:c:r:n:b:dxh"

/*************************** Function Prototypes *****************************/

static void usage(char*);
static void arg_parse(int, char**);

/******************************** Globals ************************************/

char* pname;
char* img_file_name = "C:\\Users\\acer\\Desktop\\Paper\\images\\BuildingR.jpg";    //待检测图片的绝对路径
char* out_file_name = NULL;   //导出特征点到此文件中
char* out_img_name = NULL;   //导出图片的文件名
int intvls = SIFT_INTVLS;
double sigma = SIFT_SIGMA;
double contr_thr = SIFT_CONTR_THR;
int curv_thr = SIFT_CURV_THR;
int img_dbl = SIFT_IMG_DBL;
int descr_width = SIFT_DESCR_WIDTH;
int descr_hist_bins = SIFT_DESCR_HIST_BINS;
int display = 1;


/********************************** Main *************************************/

int main(int argc, char** argv)
{
	IplImage* img;
	struct feature* features;
	int n = 0;

	//arg_parse( argc, argv );

	fprintf(stderr, "Finding SIFT features...\n");
	img = cvLoadImage(img_file_name, 1);
	if (!img)
		//fatal_error("unable to load image from %s", img_file_name);
		exit(1);
	n = _sift_features(img, &features, intvls, sigma, contr_thr, curv_thr,
		img_dbl, descr_width, descr_hist_bins);
	fprintf(stderr, "Found %d features.\n", n);

	if (display)
	{
		draw_features(img, features, n);
		cvSaveImage("C:\\Users\\acer\\Desktop\\大论文\\插图\\实验插图\\特征提取对比\\cosift_desc_right.jpg", img, 0);
		display_big_img(img, img_file_name);
		cvWaitKey(0);
	}

	if (out_file_name != NULL)
		export_features(out_file_name, features, n);

	if (out_img_name != NULL)
		cvSaveImage(out_img_name, img, NULL);
	return 0;
}