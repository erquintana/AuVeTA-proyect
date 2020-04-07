#!/usr/bin/env python3

import serial
import math

import tkinter
from tkinter import messagebox
from tkinter import ttk
import tkinter.ttk
import time
import _thread

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import time


class Interfase:
    def __init__(self):

        # fonts:
        self.TEXT_FONT = ("Helvetica", 12)
        self.NUMBER_FONT = ("Helvetica", 17)

        # COLOR STYLING CONFIG:
        #       preset 1:
#        self.windowColor = '#316893'
#        self.figureColor1 = '#316893'
#        self.letterColor1 = 'white'
#        self.figureColor2 = '#316893'
#        self.letterColor2 = 'white'
        #       preset 2:
        self.windowColor = 'white'
        self.figureColor1 = 'white'
        self.letterColor1 = 'black'
        self.figureColor2 = 'white'
        self.letterColor2 = 'black'

        # place in window 1080/5 = 216      720/10 = 72
        self.resolution = "1920x720"
        self.MX = 100
        self.MY = 75
        self.xCorrection = 20
        self.yCorrection = -5
        self.state = 0  # 0 = rec OFF  //  1 =  rec ON

        # UTILITY VARIABLES:
        self.timeDataToPlot = []
        self.frecDataToPlot = []
        self.distDataToPlot = []
        self.velDataToPlot = []

        # CREATING MAIN WINDOW:
        self.window = tkinter.Tk()
        self.window.title("RaQun's Spinmetter")
        self.window.geometry(self.resolution+"+0+0")
#        self.window.resizable(0, 0)
        self.window.configure(background=self.windowColor)

#        # DRAWING STYLE:
#        self.draw0 = tkinter.Canvas(self.window, width=475, height=350)
#        self.draw0.create_rectangle(
#            0, 0, 550, 400, outline=self.figureColor1, fill=self.figureColor1)
#        self.draw0.place(x=20, y=20)

        #   MAIN TEXTLABEL CREATIONS:
        self.buildMainLabels()

        # PLOTS CREATION:
        fig1 = Figure(figsize=(13, 5))
        #   VEL
        self.vp = fig1.add_subplot(121)

        self.fp = fig1.add_subplot(122)
        self.fp.set_xlabel("Frequency (Hz)")
        self.fp.set_ylabel("Time (s)")

        self.graph1 = FigureCanvasTkAgg(fig1, master=self.window)
        self.graph1.get_tk_widget().place(x=self.MX*6-10, y=self.MY-115)

        #   MAIN DATALABEL CREATIONS:
        self.timeDataLabel = tkinter.Label(self.window)
        self.frecDataLabel = tkinter.Label(self.window)
        self.distanceDataLabel = tkinter.Label(self.window)
        self.velDataLabel = tkinter.Label(self.window)
        self.maxVelDataLabel = tkinter.Label(self.window)

        # TIME DATA
        self.timeDataLabel.configure(
            font=self.NUMBER_FONT, background=self.figureColor2, fg=self.letterColor2)
        self.timeDataLabel.place(
            x=self.MX*2+self.xCorrection, y=self.MY*1+self.yCorrection)
        # FREC DATA
        self.frecDataLabel.configure(
            font=self.NUMBER_FONT, background=self.figureColor2, fg=self.letterColor2)
        self.frecDataLabel.place(
            x=self.MX*2+self.xCorrection, y=self.MY*2+self.yCorrection)
        # DIST DATA
        self.distanceDataLabel.configure(
            font=self.NUMBER_FONT, background=self.figureColor2, fg=self.letterColor2)
        self.distanceDataLabel.place(
            x=self.MX*2+self.xCorrection, y=self.MY*3+self.yCorrection)
        # VEL DATA
        self.velDataLabel.configure(
            font=self.NUMBER_FONT, background=self.figureColor2, fg=self.letterColor2)
        self.velDataLabel.place(
            x=self.MX*2+self.xCorrection, y=self.MY*4+self.yCorrection)
        # MAX VEL DATA
        self.maxVelDataLabel.configure(
            font=self.NUMBER_FONT, background=self.figureColor2, fg=self.letterColor2)
        self.maxVelDataLabel.place(
            x=self.MX*2+self.xCorrection, y=self.MY*5+self.yCorrection)

        # THREAD AND MAINLOOP:

        self.window.after(300, _thread.start_new_thread, self.getDataFromCSV, ())
        self.window.after(300, _thread.start_new_thread, self.plotter, ())
        self.window.mainloop()
        
    ################### DEF FUNCTIONS ###################

    # BUILDER OF MAIN LABELS
    def buildMainLabels(self):
        textList = ["Activity time:", "Current freq:", "Distance:", "Current speed:","Max speed:"]
        for i in range(0, len(textList)):
            self.myLabelTextCreate(
                self.window, textList[i], self.TEXT_FONT, self.MX, self.MY*(i+1))
    # CREATOR FOR TEXT LABELS

    def myLabelTextCreate(self, parent, t, textFont, mx, my):
        lab = tkinter.Label(parent)
        lab.configure(text=t, font=textFont,
                      background=self.figureColor1, fg=self.letterColor1)
        lab.place(x=mx, y=my)

    # PLOTTER FUNC:
    def plotter(self):
        while True:            
            self.vp.cla()
            self.vp.set_ylabel("Velocity (km/h)")
            self.vp.set_xlabel("Time (s)")
            self.vp.set_ylim(bottom=-3, top=60)
            self.vp.plot(self.timeDataToPlot, self.velDataToPlot,
                         marker='o', color='tab:blue', markersize=2)

            self.fp.cla()
            self.fp.set_ylabel("Distance (m)")
            self.fp.set_xlabel("Time (s)")
            self.fp.plot(self.timeDataToPlot, self.distDataToPlot,
                         marker='o', color='tab:red', markersize=2)

            self.graph1.draw()

    # DATA GETTING FUNC:

    def getDataFromCSV(self):

        t0 = '0'
        f0 = 0
        d0 = 0
        v0 = 0
        maxVel0 = 0

        while(1):
            ##################################################
                #   LECTURA DE ARCHIVOS ACÁ
            
            
            ##################################################
            values = serialValues.split(',')
            
            th = values[0]
            tm = values[1]
            ts = values[2]
            timeInSeconds = float(th)*3600+float(tm)*60+float(ts)

            # REMEMBER TO CHECK THIS DATA:
            f0 = round(float(values[3]), 2)
            d0 = round(d0+2*math.pi*f0*0.736*1, 3)
            v0 = round(2*math.pi*f0*0.736, 2)

            if(v0>maxVel0):
                maxVel0 = v0
            ################################
            t = "  "+th + " h     "+tm + " min     " + ts+" s  "
            f = "  "+str(f0)+" Hz  "
            d = "  "+str(d0)+" m  "
            v = "  "+str(v0)+" km/h  "
            maxVel = str(maxVel0)+' km/h'
            


            self.timeDataToPlot.append(timeInSeconds)
            self.frecDataToPlot.append(f0)
            self.distDataToPlot.append(d0)
            self.velDataToPlot.append(v0)

            self.timeDataLabel.configure(text=t)
            self.frecDataLabel.configure(text=f)
            self.distanceDataLabel.configure(text=d)
            self.velDataLabel.configure(text=v)
            self.maxVelDataLabel.configure(text=maxVel)
        arduino.close()


myGUI = Interfase()
