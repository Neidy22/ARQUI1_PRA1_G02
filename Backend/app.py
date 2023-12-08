from tkinter import *
from tkinter import ttk
from api import Api
from connection import Connection

console_log = ''
TKN_ACCESS= ''
serial_conn = Connection()

class App():

    def __init__(self):
        self.console_log = ''
        self.root = Tk()
        self.root.title("Iniciar")
        self.root.geometry('850x400')
        self.root.resizable(False, False)
        
        self.tkn_label = ttk.Label(self.root, text='Token')
        self.tkn_label.place(x=10, y=50, width=50)

        self.tkn = Entry(self.root)
        self.tkn.place(x=100, y=50, width=600)

        self.com_label = ttk.Label(self.root, text='Puerto')
        self.com_label.place(x=10, y=100, width=50)

        self.com = Entry(self.root)
        self.com.place(x=100, y=100, width=600)

        self.response_label = ttk.Label(self.root, text='')
        self.response_label.place(x=100, y=200, width=600)

        def get_connection():
            global TKN_ACCESS
            TKN_ACCESS = self.tkn.get()
            COM = self.com.get()
            
            if TKN_ACCESS != '' and COM != '':
                if serial_conn.new_connection(COM, 9600):
                    self.root.destroy()
                    showMain()
                else:
                    self.response_label.config(text="ERROR! No se pudo conectar al bluetooth")
            else:
                self.response_label.config(text="ERROR! Debes introducir un token de acceso y un puerto COM")
            

        self.btn = ttk.Button(self.root, text='Connect',
                              command=get_connection)
        self.btn.pack()
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
        response = Api.posts_from_fb(TKN_ACCESS)
        #console_log = serial_conn.check_for_new_orders(response['data'],2)
        console_log = response
        consola_out.insert('end', console_log)

    def close_app():
        serial_conn.close_connection()
        v.destroy()

    b = ttk.Button(v, text="Respuesta", command=get_console_log)
    b.place(x=700, y=175)

    bCerrarS = ttk.Button(v, text="Cerrar",
                          command=close_app, width=12)
    bCerrarS.place(x=375, y=650)

    # console log
    consola_out = Text(v, height=10, width=90)
    consola_out.place(x=50, y=205)
    consola_out.insert('end', console_log)
    v.mainloop()


App()

