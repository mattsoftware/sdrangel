///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017-2020, 2022 Edouard Griffiths, F4EXB <f4exb06@gmail.com>    //
// Copyright (C) 2022 Jon Beniston, M7RCE <jon@beniston.com>                     //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef PLUGINS_SAMPLESOURCE_LIMESDRINPUT_LIMESDRINPUTGUI_H_
#define PLUGINS_SAMPLESOURCE_LIMESDRINPUT_LIMESDRINPUTGUI_H_

#include <device/devicegui.h>
#include <QTimer>
#include <QWidget>

#include "util/messagequeue.h"

#include "limesdrinput.h"

class DeviceUISet;

namespace Ui {
    class LimeSDRInputGUI;
}

class LimeSDRInputGUI : public DeviceGUI {
    Q_OBJECT

public:
    explicit LimeSDRInputGUI(DeviceUISet *deviceUISet, QWidget* parent = 0);
    virtual ~LimeSDRInputGUI();
    virtual void destroy();

    void resetToDefaults();
    QByteArray serialize() const;
    bool deserialize(const QByteArray& data);
    virtual MessageQueue *getInputMessageQueue() { return &m_inputMessageQueue; }
    void setReplayTime(float time) override;

private:
    Ui::LimeSDRInputGUI* ui;

    LimeSDRInput* m_limeSDRInput; //!< Same object as above but gives easy access to LimeSDRInput methods and attributes that are used intensively
    LimeSDRInputSettings m_settings;
    QList<QString> m_settingsKeys;
    bool m_sampleRateMode; //!< true: device, false: base band sample rate update mode
    QTimer m_updateTimer;
    QTimer m_statusTimer;
    int m_sampleRate;
    quint64 m_deviceCenterFrequency; //!< Center frequency in device
    int m_lastEngineState;
    bool m_doApplySettings;
    bool m_forceSettings;
    int m_statusCounter;
    int m_deviceStatusCounter;
    MessageQueue m_inputMessageQueue;

    void displaySettings();
    void displaySampleRate();
	void displayReplayLength();
	void displayReplayOffset();
	void displayReplayStep();
    void setNCODisplay();
    void setCenterFrequencyDisplay();
    void setCenterFrequencySetting(uint64_t kHzValue);
    void sendSettings();
    void updateSampleRateAndFrequency();
    void checkLPF();
    void updateADCRate();
    void updateFrequencyLimits();
    void blockApplySettings(bool block);
    bool handleMessage(const Message& message);
    void makeUIConnections();

private slots:
    void handleInputMessages();
    void on_startStop_toggled(bool checked);
    void on_centerFrequency_changed(quint64 value);
    void on_ncoFrequency_changed(qint64 value);
    void on_ncoEnable_toggled(bool checked);
    void on_dcOffset_toggled(bool checked);
    void on_splitFreq_toggled(bool checked);
    void on_iqImbalance_toggled(bool checked);
    void on_sampleRate_changed(quint64 value);
    void on_hwDecim_currentIndexChanged(int index);
    void on_swDecim_currentIndexChanged(int index);
    void on_lpf_changed(quint64 value);
    void on_lpFIREnable_toggled(bool checked);
    void on_lpFIR_changed(quint64 value);
    void on_gainMode_currentIndexChanged(int index);
    void on_gain_valueChanged(int value);
    void on_lnaGain_valueChanged(int value);
    void on_tiaGain_currentIndexChanged(int index);
    void on_pgaGain_valueChanged(int value);
    void on_antenna_currentIndexChanged(int index);
    void on_extClock_clicked();
    void on_transverter_clicked();
    void on_sampleRateMode_toggled(bool checked);
  	void on_replayOffset_valueChanged(int value);
	void on_replayNow_clicked();
	void on_replayPlus_clicked();
	void on_replayMinus_clicked();
	void on_replaySave_clicked();
	void on_replayLoop_toggled(bool checked);
    void openDeviceSettingsDialog(const QPoint& p);

    void updateHardware();
    void updateStatus();
};

#endif /* PLUGINS_SAMPLESOURCE_LIMESDRINPUT_LIMESDRINPUTGUI_H_ */
