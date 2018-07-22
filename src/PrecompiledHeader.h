#ifndef _PRECOMPILEDHEADER_H_
#define _PRECOMPILEDHEADER_H_

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#endif // __TPRECOMPILEDHEADER_H__