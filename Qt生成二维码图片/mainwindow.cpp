#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "QrCode.hpp"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString tempstr = ui->lineEdit->text();
    GenerateQRcode(tempstr);
}

//生成二维码图片
void MainWindow::GenerateQRcode(QString tempstr)
{
	const char *text = "Hello, world!";              // User-supplied text
	const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

	// Make and print the QR Code symbol
	const QrCode qr = QrCode::encodeText(tempstr.toLocal8Bit().data(), errCorLvl);
	int border = 0;
	int nY = 0;
	int nX = 0;
	for (int y = -border; y < qr.getSize() + border; y++)
	{
		for (int x = -border; x < qr.getSize() + border; x++)
		{
			nX++;
		}
		nY++;
	}

	//QRcode *qrcode; //二维码数据
	////QR_ECLEVEL_Q 容错等级
	//qrcode = QRcode_encodeString(tempstr.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
	qint32 temp_width = ui->label_5->width(); //二维码图片的大小
	qint32 temp_height = ui->label_5->height();
	
	qint32 qrcode_width = nY > 0 ? nY : 1;
	double scale_x = (double)temp_width / (double)qrcode_width; //二维码图片的缩放比例
	double scale_y = (double)temp_height / (double)qrcode_width;
	QImage mainimg = QImage(temp_width, temp_height, QImage::Format_ARGB32);
	QPainter painter(&mainimg);
	QColor background(Qt::white);
	painter.setBrush(background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, temp_width, temp_height);
	QColor foreground(Qt::black);
	painter.setBrush(foreground);

	for (int y = -border; y < qr.getSize() + border; y++)
	{
		for (int x = -border; x < qr.getSize() + border; x++)
		{
			nX++;
			if (qr.getModule(x, y))
			{
				QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
				painter.drawRects(&r, 1);
			}
			else
			{

			}			
		}
		nY++;
	}
	QPixmap mainmap = QPixmap::fromImage(mainimg);
	ui->label_5->setPixmap(mainmap);
	ui->label_5->setVisible(true);
}
