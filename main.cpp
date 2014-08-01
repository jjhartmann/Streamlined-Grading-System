#include "Controller/loginview.h"
#include "Controller/viewcontroller.h"
#include <QApplication>

//Test
#include "testform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ViewController v;
    v.initializeLoginView();

    //TESTING
    //    TestForm test;
    //    test.show();

    //    v.ShowInstructorView();

    return a.exec();


}
