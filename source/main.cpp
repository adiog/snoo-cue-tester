// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <udpbox.h>
#include <iostream>
#include <GL/glut.h>
#include <component/Scene.h>
#include <network/Dispatcher.h>
#include <network/Matcher.h>
#include <opengl/ContextMenu.h>
#include <opengl/Display.h>
#include <opengl/KeyboardController.h>
#include <opengl/MouseController.h>
#include <sensor/Sensor.h>


template <typename OnLoadCallback>
int main_opengl(int argc, char** argv, OnLoadCallback onLoadCallback)
{
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 800;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("snoo-cue-tester");

    OrbitCamera::resetCamera();
    Display::intialization();
    glutReshapeFunc(Display::rashape);
    glutDisplayFunc(Display::display);
    glutIdleFunc(Display::display);
    glutMotionFunc(MouseController::pressedMouseCallback);
    glutMouseFunc(MouseController::mouseCallback);
    glutPassiveMotionFunc(MouseController::passiveMouseCallback);
    ContextMenu::createContextMenu();
    glutKeyboardFunc(KeyboardController::keyboardCallback);
    Display::redisplay();
    onLoadCallback();
    glutMainLoop();

    return 0;
}


int main(int argc, char** argv)
{
    openGLContext.sampleModel.emplace(std::make_pair(sensor::Segment::SegmentY, sensor::Sensor()));

    openGLContext.scene.apply(openGLContext.sampleModel.getLayout());

    udpbox::OnDatagramCallback callback = [&](udpbox::Datagram&& datagram) {
        sensor::Segment segment = network::Matcher::match(datagram);
        sensorFusion::SensorData sensorData = network::Dispatcher::dispatch(datagram);
        openGLContext.sampleModel.at(segment).update(sensorData);
        openGLContext.scene.apply(openGLContext.sampleModel.getLayout());
    };

    udpbox::Server server(1234);
    server.setOnDatagramCallback(callback);

    main_opengl(argc, argv,
                [&server]() {
                    server.start();
                });

    return 0;
}
