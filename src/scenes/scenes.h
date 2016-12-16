//#define _DEBUG

#define APP_WIDTH 640.0
#define APP_HEIGHT 1136.0

#define BUTTON_WIDTH (500*ofGetWidth()/APP_WIDTH)
#define BUTTON_HEIGHT (80*ofGetWidth()/APP_WIDTH)

#include "InicioScene.h"
class InicioScene;
#define INICIO_SCENE_NAME "Inicio"

#include "QRScene.h"
class QRScene;
#define QR_SCENE_NAME "QR"

#include "PostScene.h"
class PostScene;
#define POST_SCENE_NAME "Post"

#include "DatosScene.h"
class DatosScene;
#define DATOS_SCENE_NAME "Datos"

#include "ErrorScene.h"
class ErrorScene;
#define ERROR_SCENE_NAME "Error"
