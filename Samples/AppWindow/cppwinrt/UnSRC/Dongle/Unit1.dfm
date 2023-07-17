object Form1: TForm1
  Left = 188
  Top = 102
  Width = 619
  Height = 331
  Caption = 'K8055 USB Experiment Interface Board'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 92
    Width = 15
    Height = 13
    Caption = '- - -'
  end
  object OutputTest1: TSpeedButton
    Left = 8
    Top = 272
    Width = 105
    Height = 25
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Output Test'
    OnClick = OutputTest1Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 105
    Height = 41
    Caption = 'Card Address'
    TabOrder = 0
    object CheckBox1: TCheckBox
      Left = 8
      Top = 16
      Width = 41
      Height = 17
      Caption = 'SK5'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 56
      Top = 16
      Width = 41
      Height = 17
      Caption = 'SK6'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
  end
  object Connect1: TButton
    Left = 8
    Top = 56
    Width = 105
    Height = 29
    Caption = 'Connect'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = Connect1Click
  end
  object GroupBox2: TGroupBox
    Left = 128
    Top = 8
    Width = 49
    Height = 289
    Caption = 'DA1'
    TabOrder = 2
    object Label2: TLabel
      Left = 16
      Top = 272
      Width = 15
      Height = 13
      Caption = '00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object DAC1: TTrackBar
      Left = 8
      Top = 16
      Width = 33
      Height = 257
      Max = 255
      Orientation = trVertical
      Frequency = 10
      Position = 255
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      ThumbLength = 15
      TickMarks = tmTopLeft
      TickStyle = tsAuto
      OnChange = DAC1Change
    end
  end
  object GroupBox3: TGroupBox
    Left = 184
    Top = 8
    Width = 49
    Height = 289
    Caption = 'DA2'
    TabOrder = 3
    object Label3: TLabel
      Left = 16
      Top = 272
      Width = 15
      Height = 13
      Caption = '00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object DAC2: TTrackBar
      Left = 8
      Top = 16
      Width = 33
      Height = 257
      Max = 255
      Orientation = trVertical
      Frequency = 10
      Position = 255
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      ThumbLength = 15
      TickMarks = tmTopLeft
      TickStyle = tsAuto
      OnChange = DAC2Change
    end
  end
  object GroupBox4: TGroupBox
    Left = 248
    Top = 8
    Width = 49
    Height = 289
    Caption = 'AD1'
    TabOrder = 4
    object Label4: TLabel
      Left = 16
      Top = 272
      Width = 15
      Height = 13
      Caption = '00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object AD1: TProgressBar
      Left = 16
      Top = 24
      Width = 17
      Height = 241
      Min = 0
      Max = 255
      Orientation = pbVertical
      Smooth = True
      TabOrder = 0
    end
  end
  object SetAllDigital1: TButton
    Left = 8
    Top = 156
    Width = 105
    Height = 21
    Caption = 'Set All Digital'
    TabOrder = 5
    OnClick = SetAllDigital1Click
  end
  object ClearAllDigital1: TButton
    Left = 8
    Top = 180
    Width = 105
    Height = 21
    Caption = 'Clear All Digital'
    TabOrder = 6
    OnClick = ClearAllDigital1Click
  end
  object SetAllAnalog1: TButton
    Left = 8
    Top = 212
    Width = 105
    Height = 21
    Caption = 'Set All Analog'
    TabOrder = 7
    OnClick = SetAllAnalog1Click
  end
  object ClearAllAnalog1: TButton
    Left = 8
    Top = 236
    Width = 105
    Height = 21
    Caption = 'Clear All Analog'
    TabOrder = 8
    OnClick = ClearAllAnalog1Click
  end
  object GroupBox5: TGroupBox
    Left = 304
    Top = 8
    Width = 49
    Height = 289
    Caption = 'AD2'
    TabOrder = 9
    object Label5: TLabel
      Left = 16
      Top = 272
      Width = 15
      Height = 13
      Caption = '00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object AD2: TProgressBar
      Left = 16
      Top = 24
      Width = 17
      Height = 241
      Min = 0
      Max = 255
      Orientation = pbVertical
      Smooth = True
      TabOrder = 0
    end
  end
  object GroupBox6: TGroupBox
    Left = 364
    Top = 8
    Width = 161
    Height = 45
    Caption = 'Inputs'
    TabOrder = 10
    object CheckBox3: TCheckBox
      Left = 12
      Top = 20
      Width = 25
      Height = 13
      Caption = '1'
      TabOrder = 0
    end
    object CheckBox4: TCheckBox
      Left = 40
      Top = 20
      Width = 25
      Height = 13
      Caption = '2'
      TabOrder = 1
    end
    object CheckBox5: TCheckBox
      Left = 72
      Top = 20
      Width = 25
      Height = 13
      Caption = '3'
      TabOrder = 2
    end
    object CheckBox6: TCheckBox
      Left = 100
      Top = 20
      Width = 25
      Height = 13
      Caption = '4'
      TabOrder = 3
    end
    object CheckBox7: TCheckBox
      Left = 128
      Top = 20
      Width = 25
      Height = 13
      Caption = '5'
      TabOrder = 4
    end
  end
  object GroupBox7: TGroupBox
    Left = 364
    Top = 60
    Width = 241
    Height = 45
    Caption = 'Outputs'
    TabOrder = 11
  end
  object GroupBox8: TGroupBox
    Left = 364
    Top = 116
    Width = 117
    Height = 181
    Caption = 'Counter1'
    TabOrder = 12
    object Counter1: TEdit
      Left = 12
      Top = 20
      Width = 93
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '0'
    end
    object ResetCounter1: TButton
      Left = 12
      Top = 48
      Width = 93
      Height = 21
      Caption = 'Reset'
      TabOrder = 1
      OnClick = ResetCounter1Click
    end
    object DebounceTime1: TRadioGroup
      Left = 12
      Top = 76
      Width = 93
      Height = 97
      Caption = 'Debounce Time'
      ItemIndex = 1
      Items.Strings = (
        '0ms'
        '2ms'
        '10ms'
        '1000ms')
      TabOrder = 2
      OnClick = DebounceTime1Click
    end
  end
  object GroupBox9: TGroupBox
    Left = 488
    Top = 116
    Width = 117
    Height = 181
    Caption = 'Counter2'
    TabOrder = 13
    object Counter2: TEdit
      Left = 12
      Top = 20
      Width = 93
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '0'
    end
    object ResetCounter2: TButton
      Left = 12
      Top = 48
      Width = 93
      Height = 21
      Caption = 'Reset'
      TabOrder = 1
      OnClick = ResetCounter2Click
    end
    object DebounceTime2: TRadioGroup
      Left = 12
      Top = 76
      Width = 93
      Height = 97
      Caption = 'Debounce Time'
      ItemIndex = 1
      Items.Strings = (
        '0ms'
        '2ms'
        '10ms'
        '1000ms')
      TabOrder = 2
      OnClick = DebounceTime2Click
    end
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 12
    Top = 120
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer2Timer
    Left = 48
    Top = 120
  end
end
