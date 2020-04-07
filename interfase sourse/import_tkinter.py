import tkinter
import tkinter.messagebox
import time
import random
import _thread

class Menu:

    def __init__(self):    

        self.main_window = tkinter.Tk()
        self.main_window.title("Room Light System")
        self.main_window.geometry("1200x600")


        #Frames
        self.frame_2 = tkinter.Frame(self.main_window, bg='Orange') # Receiving DATAs



        #ReceiveLabel
        self.ReceiveLabel = tkinter.Label(self.frame_2,\
                                       text = 'Received DATAs',\
                                       bg = 'White',\
                                       height = 2, width = 20)


        #Temperature
        self.GetTempLabel = tkinter.Label(self.frame_2,\
                                       text='Temperature :')
        self.TempValue = tkinter.StringVar()

        self.GetTempValueLabel = tkinter.Label(self.frame_2,bg = 'Green',\
                                               textvariable = self.TempValue
                                               )



        #PACKING!!! F2

        self.frame_2.pack()
        self.frame_2.place(x=410, y=0, height=300, width=400)
        #ReceiveLabel
        self.ReceiveLabel.pack()
        self.ReceiveLabel.place(x=100, y=10)
        #Temperature
        self.GetTempLabel.pack()
        self.GetTempLabel.place(x=50, y=80, height=20, width=120)
        self.GetTempValueLabel.pack()
        self.GetTempValueLabel.place(x=200, y=80, height=20, width=50)


        #main loop and quit
        self.quitButton = tkinter.Button(self.main_window,\
                                          text = 'Quit',
                                          command = self.main_window.destroy,\
                                          height = 2, width = 6)
        self.quitButton.pack() 

        self.quitButton.place(x=200, y=500)


        self.main_window.after(2000, _thread.start_new_thread, self.GetTemp, ())
        tkinter.mainloop()

    def GetTemp(self):

        while(1):
            value = random.random()
            self.TempValue.set(str(value))
            time.sleep(0.5)

gui = Menu()