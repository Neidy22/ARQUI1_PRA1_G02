from tkinter import *
from tkinter import ttk
import requests
from api import Api

console_log = ''
TKN_ACCESS= ''

class App():

    def __init__(self):
        self.console_log = ''
        self.root = Tk()
        self.root.title("Iniciar")
        self.root.geometry('850x700')
        self.root.resizable(False, False)
        

        self.tkn = Entry(self.root)
        self.tkn.place(x=50, y=50, width=600)

        def get_connection():
            global TKN_ACCESS
            TKN_ACCESS = self.tkn.get()
            print(TKN_ACCESS)
            if TKN_ACCESS != '':
                self.root.destroy()
                showMain()
            

        self.btn = ttk.Button(self.root, text='Connect',
                              command=get_connection)
        self.btn.pack()
        self.response_label = ttk.Label(self.root, text='')
        self.response_label.pack()
        self.root.mainloop()
        

def showMain():  
    v = Tk()
    v.title("Página de Inicio")
    v.geometry('850x700')
    v.resizable(False, False)
    

    v['bg'] = 'gray'
    t = ttk.Label(v, text="STATUS", background='gray')
    t.place(x=50, y=185)

    def get_console_log():
        consola_out.delete('1.0', END)
        console_log = Api.posts_from_fb(TKN_ACCESS)
        consola_out.insert('end', console_log)

    b = ttk.Button(v, text="Respuesta", command=get_console_log)
    b.place(x=700, y=175)

    bCerrarS = ttk.Button(v, text="Cerrar",
                          command=v.destroy, width=12)
    bCerrarS.place(x=375, y=650)

    # console log
    consola_out = Text(v, height=10, width=90)
    consola_out.place(x=50, y=205)
    consola_out.insert('end', console_log)
    v.mainloop()


App()

