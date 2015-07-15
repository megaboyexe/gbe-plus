// GB Enhanced+ Copyright Daniel Baxter 2015
// Licensed under the GPLv2
// See LICENSE.txt for full license text

// File : general_settings.h
// Date : June 28, 2015
// Description : Main menu
//
// Dialog for various options
// Deals with Graphics, Audio, Input, Paths, etc

#include <iostream>

#include "general_settings.h"
#include "main_menu.h"
#include "qt_common.h"

#include "common/config.h"

core_emu* main_menu::gbe_plus = NULL;

/****** General settings constructor ******/
gen_settings::gen_settings(QWidget *parent) : QDialog(parent)
{
	//Set up tabs
	tabs = new QTabWidget(this);
	
	QDialog* general = new QDialog;
	QDialog* display = new QDialog;
	QDialog* sound = new QDialog;
	QDialog* controls = new QDialog;
	QDialog* paths = new QDialog;

	tabs->addTab(general, tr("General"));
	tabs->addTab(display, tr("Display"));
	tabs->addTab(sound, tr("Sound"));
	tabs->addTab(controls, tr("Controls"));
	tabs->addTab(paths, tr("Paths"));

	tabs_button = new QDialogButtonBox(QDialogButtonBox::Close);

	//General settings - Emulated system type
	QWidget* sys_type_set = new QWidget(general);
	QLabel* sys_type_label = new QLabel("Emulated System Type : ", sys_type_set);
	sys_type = new QComboBox(sys_type_set);
	sys_type->addItem("Auto");
	sys_type->addItem("Game Boy [DMG]");
	sys_type->addItem("Game Boy Color [GBC]");
	sys_type->addItem("Game Boy Advance [GBA]");

	QHBoxLayout* sys_type_layout = new QHBoxLayout;
	sys_type_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	sys_type_layout->addWidget(sys_type_label);
	sys_type_layout->addWidget(sys_type);
	sys_type_set->setLayout(sys_type_layout);

	//General settings - Use BIOS
	QWidget* bios_set = new QWidget(general);
	QLabel* bios_label = new QLabel("Use BIOS/Boot ROM", bios_set);
	bios = new QCheckBox(bios_set);

	QHBoxLayout* bios_layout = new QHBoxLayout;
	bios_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	bios_layout->addWidget(bios);
	bios_layout->addWidget(bios_label);
	bios_set->setLayout(bios_layout);

	QVBoxLayout* gen_layout = new QVBoxLayout;
	gen_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	gen_layout->addWidget(sys_type_set);
	gen_layout->addWidget(bios_set);
	general->setLayout(gen_layout);

	//Display settings - Screen scale
	QWidget* screen_scale_set = new QWidget(display);
	QLabel* screen_scale_label = new QLabel("Screen Scale : ");
	screen_scale = new QComboBox(screen_scale_set);
	screen_scale->addItem("1x");
	screen_scale->addItem("2x");
	screen_scale->addItem("3x");
	screen_scale->addItem("4x");
	screen_scale->addItem("5x");
	screen_scale->addItem("6x");
	screen_scale->addItem("7x");
	screen_scale->addItem("8x");
	screen_scale->addItem("9x");
	screen_scale->addItem("10x");

	QHBoxLayout* screen_scale_layout = new QHBoxLayout;
	screen_scale_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	screen_scale_layout->addWidget(screen_scale_label);
	screen_scale_layout->addWidget(screen_scale);
	screen_scale_set->setLayout(screen_scale_layout);

	//Display settings - Use OpenGL
	QWidget* ogl_set = new QWidget(display);
	QLabel* ogl_label = new QLabel("Use OpenGL");
	ogl = new QCheckBox(ogl_set);

	QHBoxLayout* ogl_layout = new QHBoxLayout;
	ogl_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	ogl_layout->addWidget(ogl);
	ogl_layout->addWidget(ogl_label);
	ogl_set->setLayout(ogl_layout);

	QVBoxLayout* disp_layout = new QVBoxLayout;
	disp_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	disp_layout->addWidget(screen_scale_set);
	disp_layout->addWidget(ogl_set);
	display->setLayout(disp_layout);

	//Sound settings - Output frequency
	QWidget* freq_set = new QWidget(sound);
	QLabel* freq_label = new QLabel("Output Frequency : ");
	freq = new QComboBox(freq_set);
	freq->addItem("48000Hz");
	freq->addItem("44100Hz");
	freq->addItem("20500Hz");
	freq->addItem("10250Hz");
	freq->setCurrentIndex(1);

	QHBoxLayout* freq_layout = new QHBoxLayout;
	freq_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	freq_layout->addWidget(freq_label);
	freq_layout->addWidget(freq);
	freq_set->setLayout(freq_layout);

	//Sound settings - Sound on/off
	QWidget* sound_on_set = new QWidget(sound);
	QLabel* sound_on_label = new QLabel("Enable Sound");
	sound_on = new QCheckBox(sound_on_set);
	sound_on->setChecked(true);

	QHBoxLayout* sound_on_layout = new QHBoxLayout;
	sound_on_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	sound_on_layout->addWidget(sound_on);
	sound_on_layout->addWidget(sound_on_label);
	sound_on_set->setLayout(sound_on_layout);

	//Sound settings - Volume
	QWidget* volume_set = new QWidget(sound);
	QLabel* volume_label = new QLabel("Volume : ");
	volume = new QSlider(sound);
	volume->setMaximum(128);
	volume->setMinimum(0);
	volume->setValue(128);
	volume->setOrientation(Qt::Horizontal);

	QHBoxLayout* volume_layout = new QHBoxLayout;
	volume_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	volume_layout->addWidget(volume_label);
	volume_layout->addWidget(volume);
	volume_set->setLayout(volume_layout);

	QVBoxLayout* audio_layout = new QVBoxLayout;
	audio_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	audio_layout->addWidget(freq_set);
	audio_layout->addWidget(sound_on_set);
	audio_layout->addWidget(volume_set);
	sound->setLayout(audio_layout);


	//Control settings - Device
	QWidget* input_device_set = new QWidget(controls);
	QLabel* input_device_label = new QLabel("Input Device : ");
	input_device = new QComboBox(input_device_set);
	input_device->addItem("Keyboard");

	QHBoxLayout* input_device_layout = new QHBoxLayout;
	input_device_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	input_device_layout->addWidget(input_device_label);
	input_device_layout->addWidget(input_device);
	input_device_set->setLayout(input_device_layout);

	//Control settings - A button
	QWidget* input_a_set = new QWidget(controls);
	QLabel* input_a_label = new QLabel("Button A : ");
	input_a = new QLineEdit(controls);
	config_a = new QPushButton("Configure");
	input_a->setMaximumWidth(100);
	config_a->setMaximumWidth(100);

	QHBoxLayout* input_a_layout = new QHBoxLayout;
	input_a_layout->addWidget(input_a_label, 0, Qt::AlignLeft);
	input_a_layout->addWidget(input_a, 0, Qt::AlignLeft);
	input_a_layout->addWidget(config_a, 0, Qt::AlignLeft);
	input_a_layout->setContentsMargins(6, 0, 0, 0);
	input_a_set->setLayout(input_a_layout);

	//Control settings - B button
	QWidget* input_b_set = new QWidget(controls);
	QLabel* input_b_label = new QLabel("Button B : ");
	input_b = new QLineEdit(controls);
	config_b = new QPushButton("Configure");
	input_b->setMaximumWidth(100);
	config_b->setMaximumWidth(100);

	QHBoxLayout* input_b_layout = new QHBoxLayout;
	input_b_layout->addWidget(input_b_label, 0, Qt::AlignLeft);
	input_b_layout->addWidget(input_b, 0, Qt::AlignLeft);
	input_b_layout->addWidget(config_b, 0, Qt::AlignLeft);
	input_b_layout->setContentsMargins(6, 0, 0, 0);
	input_b_set->setLayout(input_b_layout);

	//Control settings - START button
	QWidget* input_start_set = new QWidget(controls);
	QLabel* input_start_label = new QLabel("START : ");
	input_start = new QLineEdit(controls);
	config_start = new QPushButton("Configure");
	input_start->setMaximumWidth(100);
	config_start->setMaximumWidth(100);

	QHBoxLayout* input_start_layout = new QHBoxLayout;
	input_start_layout->addWidget(input_start_label, 0, Qt::AlignLeft);
	input_start_layout->addWidget(input_start, 0, Qt::AlignLeft);
	input_start_layout->addWidget(config_start, 0, Qt::AlignLeft);
	input_start_layout->setContentsMargins(6, 0, 0, 0);
	input_start_set->setLayout(input_start_layout);

	//Control settings - SELECT button
	QWidget* input_select_set = new QWidget(controls);
	QLabel* input_select_label = new QLabel("SELECT : ");
	input_select = new QLineEdit(controls);
	config_select = new QPushButton("Configure");
	input_select->setMaximumWidth(100);
	config_select->setMaximumWidth(100);

	QHBoxLayout* input_select_layout = new QHBoxLayout;
	input_select_layout->addWidget(input_select_label, 0, Qt::AlignLeft);
	input_select_layout->addWidget(input_select, 0, Qt::AlignLeft);
	input_select_layout->addWidget(config_select, 0, Qt::AlignLeft);
	input_select_layout->setContentsMargins(6, 0, 0, 0);
	input_select_set->setLayout(input_select_layout);

	//Control settings - Left
	QWidget* input_left_set = new QWidget(controls);
	QLabel* input_left_label = new QLabel("LEFT : ");
	input_left = new QLineEdit(controls);
	config_left = new QPushButton("Configure");
	input_left->setMaximumWidth(100);
	config_left->setMaximumWidth(100);

	QHBoxLayout* input_left_layout = new QHBoxLayout;
	input_left_layout->addWidget(input_left_label, 0, Qt::AlignLeft);
	input_left_layout->addWidget(input_left, 0, Qt::AlignLeft);
	input_left_layout->addWidget(config_left, 0, Qt::AlignLeft);
	input_left_layout->setContentsMargins(6, 0, 0, 0);
	input_left_set->setLayout(input_left_layout);

	//Control settings - Right
	QWidget* input_right_set = new QWidget(controls);
	QLabel* input_right_label = new QLabel("RIGHT : ");
	input_right = new QLineEdit(controls);
	config_right = new QPushButton("Configure");
	input_right->setMaximumWidth(100);
	config_right->setMaximumWidth(100);

	QHBoxLayout* input_right_layout = new QHBoxLayout;
	input_right_layout->addWidget(input_right_label, 0, Qt::AlignLeft);
	input_right_layout->addWidget(input_right, 0, Qt::AlignLeft);
	input_right_layout->addWidget(config_right, 0, Qt::AlignLeft);
	input_right_layout->setContentsMargins(6, 0, 0, 0);
	input_right_set->setLayout(input_right_layout);

	//Control settings - Up
	QWidget* input_up_set = new QWidget(controls);
	QLabel* input_up_label = new QLabel("UP : ");
	input_up = new QLineEdit(controls);
	config_up = new QPushButton("Configure");
	input_up->setMaximumWidth(100);
	config_up->setMaximumWidth(100);

	QHBoxLayout* input_up_layout = new QHBoxLayout;
	input_up_layout->addWidget(input_up_label, 0, Qt::AlignLeft);
	input_up_layout->addWidget(input_up, 0, Qt::AlignLeft);
	input_up_layout->addWidget(config_up, 0, Qt::AlignLeft);
	input_up_layout->setContentsMargins(6, 0, 0, 0);
	input_up_set->setLayout(input_up_layout);

	//Control settings - Down
	QWidget* input_down_set = new QWidget(controls);
	QLabel* input_down_label = new QLabel("DOWN : ");
	input_down = new QLineEdit(controls);
	config_down = new QPushButton("Configure");
	input_down->setMaximumWidth(100);
	config_down->setMaximumWidth(100);

	QHBoxLayout* input_down_layout = new QHBoxLayout;
	input_down_layout->addWidget(input_down_label, 0, Qt::AlignLeft);
	input_down_layout->addWidget(input_down, 0, Qt::AlignLeft);
	input_down_layout->addWidget(config_down, 0, Qt::AlignLeft);
	input_down_layout->setContentsMargins(6, 0, 0, 0);
	input_down_set->setLayout(input_down_layout);

	//Control settings - Right Trigger
	QWidget* input_r_set = new QWidget(controls);
	QLabel* input_r_label = new QLabel("Trigger R : ");
	input_r = new QLineEdit(controls);
	config_r = new QPushButton("Configure");
	input_r->setMaximumWidth(100);
	config_r->setMaximumWidth(100);

	QHBoxLayout* input_r_layout = new QHBoxLayout;
	input_r_layout->addWidget(input_r_label, 0, Qt::AlignLeft);
	input_r_layout->addWidget(input_r, 0, Qt::AlignLeft);
	input_r_layout->addWidget(config_r, 0, Qt::AlignLeft);
	input_r_layout->setContentsMargins(6, 0, 0, 0);
	input_r_set->setLayout(input_r_layout);

	//Control settings - Left Trigger
	QWidget* input_l_set = new QWidget(controls);
	QLabel* input_l_label = new QLabel("Trigger L : ");
	input_l = new QLineEdit(controls);
	config_l = new QPushButton("Configure");
	input_l->setMaximumWidth(100);
	config_l->setMaximumWidth(100);

	QHBoxLayout* input_l_layout = new QHBoxLayout;
	input_l_layout->addWidget(input_l_label, 0, Qt::AlignLeft);
	input_l_layout->addWidget(input_l, 0, Qt::AlignLeft);
	input_l_layout->addWidget(config_l, 0, Qt::AlignLeft);
	input_l_layout->setContentsMargins(6, 0, 0, 0);
	input_l_set->setLayout(input_l_layout);

	QVBoxLayout* controls_layout = new QVBoxLayout;
	controls_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	controls_layout->addWidget(input_device_set);
	controls_layout->addWidget(input_a_set);
	controls_layout->addWidget(input_b_set);
	controls_layout->addWidget(input_start_set);
	controls_layout->addWidget(input_select_set);
	controls_layout->addWidget(input_left_set);
	controls_layout->addWidget(input_right_set);
	controls_layout->addWidget(input_up_set);
	controls_layout->addWidget(input_down_set);
	controls_layout->addWidget(input_l_set);
	controls_layout->addWidget(input_r_set);
	controls->setLayout(controls_layout);

	//Path settings - DMG BIOS
	QWidget* dmg_bios_set = new QWidget(paths);
	dmg_bios_label = new QLabel("DMG Boot ROM :  ");
	QPushButton* dmg_bios_button = new QPushButton("Browse");
	dmg_bios = new QLineEdit(paths);
	dmg_bios->setReadOnly(true);

	QHBoxLayout* dmg_bios_layout = new QHBoxLayout;
	dmg_bios_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	dmg_bios_layout->addWidget(dmg_bios_label);
	dmg_bios_layout->addWidget(dmg_bios);
	dmg_bios_layout->addWidget(dmg_bios_button);
	dmg_bios_set->setLayout(dmg_bios_layout);
	dmg_bios_label->resize(50, dmg_bios_label->height());

	//Path settings - GBC BIOS
	QWidget* gbc_bios_set = new QWidget(paths);
	gbc_bios_label = new QLabel("GBC Boot ROM :  ");
	QPushButton* gbc_bios_button = new QPushButton("Browse");
	gbc_bios = new QLineEdit(paths);
	gbc_bios->setReadOnly(true);

	QHBoxLayout* gbc_bios_layout = new QHBoxLayout;
	gbc_bios_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	gbc_bios_layout->addWidget(gbc_bios_label);
	gbc_bios_layout->addWidget(gbc_bios);
	gbc_bios_layout->addWidget(gbc_bios_button);
	gbc_bios_set->setLayout(gbc_bios_layout);

	//Path settings - GBA BIOS
	QWidget* gba_bios_set = new QWidget(paths);
	gba_bios_label = new QLabel("GBA BIOS :  ");
	QPushButton* gba_bios_button = new QPushButton("Browse");
	gba_bios = new QLineEdit(paths);
	gba_bios->setReadOnly(true);

	QHBoxLayout* gba_bios_layout = new QHBoxLayout;
	gba_bios_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	gba_bios_layout->addWidget(gba_bios_label);
	gba_bios_layout->addWidget(gba_bios);
	gba_bios_layout->addWidget(gba_bios_button);
	gba_bios_set->setLayout(gba_bios_layout);

	QVBoxLayout* paths_layout = new QVBoxLayout;
	paths_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	paths_layout->addWidget(dmg_bios_set);
	paths_layout->addWidget(gbc_bios_set);
	paths_layout->addWidget(gba_bios_set);
	paths->setLayout(paths_layout);

	connect(tabs_button, SIGNAL(accepted()), this, SLOT(accept()));
	connect(tabs_button, SIGNAL(rejected()), this, SLOT(reject()));
	connect(bios, SIGNAL(stateChanged(int)), this, SLOT(set_bios()));
	connect(screen_scale, SIGNAL(currentIndexChanged(int)), this, SLOT(screen_scale_change()));
	connect(volume, SIGNAL(valueChanged(int)), this, SLOT(volume_change()));
	connect(freq, SIGNAL(currentIndexChanged(int)), this, SLOT(sample_rate_change()));
	connect(sound_on, SIGNAL(stateChanged(int)), this, SLOT(mute()));

	QSignalMapper* paths_mapper = new QSignalMapper(this);
	connect(dmg_bios_button, SIGNAL(clicked()), paths_mapper, SLOT(map()));
	connect(gbc_bios_button, SIGNAL(clicked()), paths_mapper, SLOT(map()));
	connect(gba_bios_button, SIGNAL(clicked()), paths_mapper, SLOT(map()));

	paths_mapper->setMapping(dmg_bios_button, 0);
	paths_mapper->setMapping(gbc_bios_button, 1);
	paths_mapper->setMapping(gba_bios_button, 2);
	connect(paths_mapper, SIGNAL(mapped(int)), this, SLOT(set_paths(int)));

	QSignalMapper* button_config = new QSignalMapper(this);
	connect(config_a, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_b, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_start, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_select, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_left, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_right, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_up, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_down, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_l, SIGNAL(clicked()), button_config, SLOT(map()));
	connect(config_r, SIGNAL(clicked()), button_config, SLOT(map()));

	button_config->setMapping(config_a, 0);
	button_config->setMapping(config_b, 1);
	button_config->setMapping(config_start, 2);
	button_config->setMapping(config_select, 3);
	button_config->setMapping(config_left, 4);
	button_config->setMapping(config_right, 5);
	button_config->setMapping(config_up, 6);
	button_config->setMapping(config_down, 7);
	button_config->setMapping(config_l, 8);
	button_config->setMapping(config_r, 9);
	connect(button_config, SIGNAL(mapped(int)), this, SLOT(configure_button(int))) ;

	//Final tab layout
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addWidget(tabs);
	main_layout->addWidget(tabs_button);
	setLayout(main_layout);

	sample_rate = config::sample_rate;
	resize_screen = false;
	grab_input = false;

	resize(450, 450);
	setWindowTitle(tr("GBE+ Settings"));
}

/****** Sets various widgets to values based on the current config paramters (from .ini file) ******/
void gen_settings::set_ini_options()
{
	//Emulated system type
	sys_type->setCurrentIndex(config::gb_type);

	//BIOS or Boot ROM option
	if(config::use_bios) { bios->setChecked(true); }

	//Screen scale options
	screen_scale->setCurrentIndex(config::scaling_factor - 1);

	//OpenGL option
	if(config::use_opengl) { ogl->setChecked(true); }

	//Sample rate option
	switch((int)config::sample_rate)
	{
		case 10250: freq->setCurrentIndex(0); break;
		case 20500: freq->setCurrentIndex(1); break;
		case 41000: freq->setCurrentIndex(2); break;
		case 48000: freq->setCurrentIndex(3); break;
	}

	//Mute option
	//TODO - Add mute for .ini options

	//Volume option
	volume->setValue(config::volume);

	//BIOS and Boot ROM paths
	QString path_1(QString::fromStdString(config::dmg_bios_path));
	QString path_2(QString::fromStdString(config::gbc_bios_path));
	QString path_3(QString::fromStdString(config::agb_bios_path));

	dmg_bios->setText(path_1);
	gbc_bios->setText(path_2);
	gba_bios->setText(path_3);
}

/****** Toggles whether to use the Boot ROM or BIOS ******/
void gen_settings::set_bios()
{
	if(bios->isChecked()) { config::use_bios = true; }
	else { config::use_bios = false; }
}

/****** Changes the display scale ******/
void gen_settings::screen_scale_change()
{
	config::scaling_factor = (screen_scale->currentIndex() + 1);
	resize_screen = true;
}

/****** Dynamically changes the core's volume ******/
void gen_settings::volume_change() 
{
	if((main_menu::gbe_plus != NULL) && (sound_on->isChecked()))
	{
		main_menu::gbe_plus->update_volume(volume->value());
	}
}

/****** Mutes the core's volume ******/
void gen_settings::mute()
{
	if(main_menu::gbe_plus != NULL)
	{
		//Unmute, use slider volume
		if(sound_on->isChecked()) { main_menu::gbe_plus->update_volume(volume->value()); }

		//Mute
		else { main_menu::gbe_plus->update_volume(0); }
	}
}

/****** Changes the core's sample rate ******/
void gen_settings::sample_rate_change()
{
	switch(freq->currentIndex())
	{
		case 0: sample_rate = 48000.0; break;
		case 1: sample_rate = 41000.0; break;
		case 2: sample_rate = 20500.0; break;
		case 3: sample_rate = 10250.0; break;
	}
}

/****** Sets a path via file browser ******/
void gen_settings::set_paths(int index)
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("All files (*)"));
	if(filename.isNull()) { return; }

	switch(index)
	{
		case 0: 
			config::dmg_bios_path = filename.toStdString();
			dmg_bios->setText(filename);
			break;

		case 1:
			config::gbc_bios_path = filename.toStdString();
			gbc_bios->setText(filename);
			break;

		case 2:
			config::agb_bios_path = filename.toStdString();
			gba_bios->setText(filename);
			break;
	}
}

/****** Prepares GUI to receive input for controller configuration ******/
void gen_settings::configure_button(int button)
{
	if(!grab_input)
	{
		switch(button)
		{
			case 0: 
				config_a->setText("Enter Input");
				break;

			case 1: 
				config_b->setText("Enter Input");
				break;

			case 2: 
				config_start->setText("Enter Input");
				break;

			case 3: 
				config_select->setText("Enter Input");
				break;

			case 4: 
				config_left->setText("Enter Input");
				break;

			case 5: 
				config_right->setText("Enter Input");
				break;

			case 6: 
				config_up->setText("Enter Input");
				break;

			case 7: 
				config_down->setText("Enter Input");
				break;

			case 8: 
				config_l->setText("Enter Input");
				break;

			case 9: 
				config_r->setText("Enter Input");
				break;
		}

		grab_input = true;
		input_index = button;
	}
}				

/****** Updates the settings window ******/
void gen_settings::paintEvent(QPaintEvent* event)
{
	gbc_bios_label->setMinimumWidth(dmg_bios_label->width());
	gba_bios_label->setMinimumWidth(dmg_bios_label->width());
}

/****** Handle keypress input ******/
void gen_settings::keyPressEvent(QKeyEvent* event)
{
	if(grab_input)
	{
		last_key = qtkey_to_sdlkey(event->key());

		switch(input_index)
		{
			case 0: 
				config_a->setText("Configure");
				input_a->setText(QString::number(last_key));
				config::agb_key_a = config::dmg_key_a = last_key;
				break;

			case 1: 
				config_b->setText("Configure");
				input_b->setText(QString::number(last_key));
				config::agb_key_b = config::dmg_key_b = last_key;
				break;

			case 2: 
				config_start->setText("Configure");
				input_start->setText(QString::number(last_key));
				config::agb_key_start = config::dmg_key_start = last_key;
				break;

			case 3: 
				config_select->setText("Configure");
				input_select->setText(QString::number(last_key));
				config::agb_key_select = config::dmg_key_select = last_key;
				break;

			case 4: 
				config_left->setText("Configure");
				input_left->setText(QString::number(last_key));
				config::agb_key_left = config::dmg_key_left = last_key;
				break;

			case 5: 
				config_right->setText("Configure");
				input_right->setText(QString::number(last_key));
				config::agb_key_right = config::dmg_key_right = last_key;
				break;

			case 6: 
				config_up->setText("Configure");
				input_up->setText(QString::number(last_key));
				config::agb_key_up = config::dmg_key_up = last_key;
				break;

			case 7: 
				config_down->setText("Configure");
				input_down->setText(QString::number(last_key));
				config::agb_key_down = config::dmg_key_down = last_key;
				break;

			case 8: 
				config_l->setText("Configure");
				input_l->setText(QString::number(last_key));
				config::agb_key_l_trigger = last_key;
				break;

			case 9: 
				config_r->setText("Configure");
				input_r->setText(QString::number(last_key));
				config::agb_key_r_trigger = last_key;
				break;
		}

		grab_input = false;
	}
}