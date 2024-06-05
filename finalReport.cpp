#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;

Mat based(506, 706, CV_8UC3, Scalar(255, 255, 255));
Point ptOld;
void on_mouse(int evnet, int x, int y, int flags, void* userdata);
void edgeLine(Mat img);
void drawText(Mat img, const string text);

Rect rectDrawing(0, 0, 506, 506);
Rect drawingSpace(3, 3, 500, 500);
Rect rectSave(506, 0, 200, 100);
Rect rectLoad(506, 100, 200, 100);
Rect rectClear(506, 200, 200, 100);
Rect rectRun(506, 300, 200, 106);
Rect rectExit(506, 406, 200, 100);

int main(void)
{
   Mat numberDrawing(506, 506, CV_8UC3, Scalar(255, 255, 255));
   edgeLine(numberDrawing);
   numberDrawing.copyTo(based(rectDrawing));

   Mat numberSave(100, 200, CV_8UC3, Scalar(255, 255, 255));
   edgeLine(numberSave);
   drawText(numberSave, "Save");
   numberSave.copyTo(based(rectSave));

   Mat numberLoad(100, 200, CV_8UC3, Scalar(255, 255, 255));
   edgeLine(numberLoad);
   drawText(numberLoad, "Load");
   numberLoad.copyTo(based(rectLoad));

   Mat numberClear(100, 200, CV_8UC3, Scalar(255, 255, 255));
   edgeLine(numberClear);
   drawText(numberClear, "Clear");
   numberClear.copyTo(based(rectClear));

   Mat numberRun(106, 200, CV_8UC3, Scalar(255, 255, 255));
   edgeLine(numberRun);
   drawText(numberRun, "Run");
   numberRun.copyTo(based(rectRun));

   Mat numberExit(100, 200, CV_8UC3, Scalar(255, 255, 255));
   edgeLine(numberExit);
   drawText(numberExit, "Exit");
   numberExit.copyTo(based(rectExit));

   Mat clearBased = based.clone();

   namedWindow("numberWindow");
   setMouseCallback("numberWindow", on_mouse, &clearBased);
   imshow("numberWindow", based);
   waitKey(0);

   return 0;
}

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
   Mat* clearBased = static_cast<Mat*>(userdata);
   switch (event)
   {
   case EVENT_LBUTTONDOWN:
      if (drawingSpace.contains(Point(x, y))) {
         ptOld = Point(x, y);
      }
      else if (rectSave.contains(Point(x, y)))
      {
         string filename;
         cout << "저장할 파일명 입력 : ";
         getline(cin, filename);
         bool saving = imwrite(filename, based(drawingSpace));
         if (saving) cout << filename << " 파일이 저장됨." << endl;
         else cout << filename << " 파일 저장실패." << endl;
      }
      else if (rectLoad.contains(Point(x, y)))
      {
         string loadFileName;
         cout << "불러올 파일명을 입력 : ";
         getline(cin, loadFileName);
         Mat temp = imread(loadFileName, IMREAD_COLOR);
         if (temp.empty()) cout << loadFileName << " 불러오기 실패." << endl;
         else cout << loadFileName << " 불러옴." << endl;
         temp.copyTo(based(drawingSpace));
         imshow("numberWindow", based);
      }
      else if (rectClear.contains(Point(x, y)))
      {
         clearBased->copyTo(based);
         imshow("numberWindow", based);
         cout << "입력창 삭제됨." << endl;
      }
      else if (rectExit.contains(Point(x, y)))
      {
         cout << "프로그램 종료" << endl;
         destroyAllWindows();
      }
      break;
   case EVENT_MOUSEMOVE:
      if (flags && EVENT_FLAG_LBUTTON && drawingSpace.contains(Point(x, y))) {
         if (drawingSpace.contains(ptOld))
         {
            line(based, ptOld, Point(x, y), Scalar(0, 0, 0), 20);
            imshow("numberWindow", based);
         }
      }
      ptOld = Point(x, y);
      break;
   default:
      break;
   }
}


void edgeLine(Mat img)
{
   line(img, Point(0, 0), Point(img.cols - 1, 0), Scalar(0, 0, 0), 3);
   line(img, Point(img.cols - 1, 0), Point(img.cols - 1, img.rows - 1), Scalar(0, 0, 0), 3);
   line(img, Point(img.cols - 1, img.rows - 1), Point(0, img.rows - 1), Scalar(0, 0, 0), 3);
   line(img, Point(0, img.rows - 1), Point(0, 0), Scalar(0, 0, 0), 3);
}

void drawText(Mat img, const string text)
{
   int fontFace = FONT_HERSHEY_SIMPLEX;
   double fontScale = 1.5;
   int thickness = 3;

   Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
   Size sizeImg = img.size();

   Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
   putText(img, text, org, fontFace, fontScale, Scalar(0, 0, 0), thickness);
}
