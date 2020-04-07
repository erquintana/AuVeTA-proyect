from tkinter import *
from tkinter import messagebox
from tkinter import ttk
from tkinter.ttk import *


def clicked():
    lbl.configure(text="Welcome to "+txt.get())
    window.title("SOMETHING HAPPENED")


def clicked2():
    lbl.configure(text="selected "+combo.get())


def clickedmessageBox():

    messagebox.showinfo("Message title", "Message content")
    # shows warning message
    messagebox.showwarning('Message title', 'Message content')
    messagebox.showerror('Message title', 'Message content')  # shows error message


window = Tk()

window.title("Welcome to LikeGeeks app")
window.geometry("1080x720+200+200")

lbl = Label(window)
lbl.configure(text="Hello", font=("Arial Bold", 50),foreground="white",background="black")
lbl.grid(column=1, row=1)


btn = Button(window, text="Click me", command=clicked)
btn.grid(column=3, row=1)

txt = Entry(window, width=15)
txt.grid(column=2, row=1)
txt.focus()

combo = Combobox(window)
combo['values'] = (1, 2, 3, 4, 5, "My Text")
combo.current(2)
combo.grid(column=4, row=1)


chk_state = BooleanVar()
chk_state.set(1)  # uncheck
chk = Checkbutton(window, text='Choose', var=chk_state)
chk.grid(column=5, row=3)


rad1 = Radiobutton(window, text='First', value=1, command=clicked2)
rad2 = Radiobutton(window, text='Second', value=2, command=clickedmessageBox)
rad3 = Radiobutton(window, text='Third', value=3)
rad1.grid(column=0, row=0)
rad2.grid(column=1, row=0)
rad3.grid(column=2, row=0)


res = messagebox.askquestion('Message title','Message content')
res = messagebox.askyesno('Message title','Message content')
res = messagebox.askyesnocancel('Message title','Message content')
res = messagebox.askokcancel('Message title','Message content')
res = messagebox.askretrycancel('Message title','Message content')


var =IntVar()
var.set(36)
spin = Spinbox(window,from_=0,to=100,width=10,textvariable=var)
#spin = Spinbox(window, values=(3, 8, 11), width=5)
spin.grid(column=7,row=7)


style = ttk.Style()
style.theme_use('default')
style.configure("black.Horizontal.TProgressbar", background='black')
bar = Progressbar(window, length=200, style='black.Horizontal.TProgressbar')
bar['value'] = var.get()
bar.grid(column=8,row=7)



window.mainloop()
