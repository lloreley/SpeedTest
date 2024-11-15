// #ifndef SPEED_TEST_HPP
// #define SPEED_TEST_HPP

// #include <QWidget>
// #include <QString>
// #include <QKeyEvent>
// #include <chrono>

// using namespace std::chrono;





// class SpeedTest : public QWidget
// {
// public:
//     SpeedTest(QWidget *parent) : QWidget(parent), levelName(""), levelText("")
//     {
//     }
//     ~SpeedTest()
//     {
//     }

// protected:
//     QString levelName;
//     QString levelText;

//     time_point<system_clock> startTime;
//     time_point<system_clock> endTime;


// private slots:
//     void keyPressEvent(QKeyEvent* event) override
//     {
        
//     }

// public slots:
//     void startTest(int levelId)
//     {

//         startTime = system_clock::now();

//         emit testStarted();
//     }




// protected slots:
//     void startTest(int testId)
//     {
        
//     }

// signals:
//     void testStarted();
//     void tesCompleted();
// };

// #endif