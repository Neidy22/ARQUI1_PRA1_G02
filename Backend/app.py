from tkinter import *
from tkinter import ttk
from api import Api
from connection import Connection

console_log = ''
last_id = ''
TKN_ACCESS= ''
serial_conn = Connection()
registered_orders = dict() # this will contain the id's of the procesed orders to detect when the user post a new order


class App():

    def __init__(self):
        self.console_log = ''
        self.root = Tk()
        self.root.title("Creacion de Conexion")
        self.root.geometry('850x400')
        self.root.resizable(False, False)
        self.root['bg'] = '#504c5f'
        font_times_new_roman = ("Times New Roman", 12)
        
        self.tkn_label = ttk.Label(self.root, text='Token',background="#504c5f")
        self.tkn_label.place(x=10, y=50, width=50)

        self.tkn = Entry(self.root
                         ,border=2
                         ,font=font_times_new_roman)
        
        self.tkn.place(x=100, y=50, width=600)

        self.com_label = ttk.Label(self.root, text='Puerto',background="#504c5f")
        self.com_label.place(x=10, y=100, width=50)

        self.com = Entry(self.root
                         ,border=2
                         ,font=font_times_new_roman)
        
        self.com.place(x=100, y=100, width=600)

        self.response_label = ttk.Label(self.root, text='',background="#504c5f")
        self.response_label.place(x=200, y=300, width=600)

        def get_connection():
            global TKN_ACCESS
            TKN_ACCESS = self.tkn.get()
            COM = self.com.get()
            
            if TKN_ACCESS != '' and COM != '':
                          
                try:
                    serial_conn.new_connection(COM, 9600)
                    self.root.destroy()
                    showMain()
                except TimeoutError:
                    self.response_label.config(text="ERROR! No se pudo conectar al bluetooth")
            else:
                self.response_label.config(text="ERROR! Debes introducir un token de acceso y un puerto COM",background="#504c5f")
            

        self.btn = ttk.Button(self.root, text='Connect',
                              command=get_connection)
        self.btn.pack()
        self.btn.place(x=310, y=200, width=200)
        self.response_label.pack()
        self.response_label.place(x=250, y=250, width=400)
        self.root.mainloop()
        

def showMain():  
    v = Tk()
    v.title("Recepcion de Pedidos")
    v.geometry('850x700')
    v.resizable(False, False)
    

    v['bg'] = '#504c5f'
    t = ttk.Label(v, text="STATUS", background='#504c5f', border=1)
    t.place(x=50, y=185)

    def check_for_new_orders(input_orders):
        for key, value in input_orders.items():
            new_order = registered_orders.get(key)

            if new_order is None:
                
                output = serial_conn.send_new_order(value)
                if output != "Error":
                    output_list = output.split(';')
                    machine_state = output_list[0].split('-')

                    console_log = f'''============================================================================================================================= \n
                                    Estado de la máquina  : {machine_state[0]} , Producto Procesado: {machine_state[1]} , Productos encolados : {output_list[9]}\n
                                    ============================================================================================================================= \n
                                    Existencia Producto 1 : {output_list[1]} , Monto Vendido Producto 1 : Q.{output_list[2]} \n
                                    Existencia Producto 2 : {output_list[3]} , Monto Vendido Producto 2 : Q.{output_list[4]} \n 
                                    Existencia Producto 3 : {output_list[5]} , Monto Vendido Producto 3 : Q.{output_list[6]} \n 
                                    Existencia Total      : {output_list[7]} , Monto Vendido Total      : Q.{output_list[8]} \n
                                    '''
                else:
                    console_log = output
                
                consola_out.insert('end', console_log)
                registered_orders[key] = value
                print(f'Nueva orden procesada {registered_orders[key]}')
            else:
                consola_out.insert('end', "Buscando nueva orden")
             
    

    def get_console_log():
        consola_out.delete('1.0', END)
        response = Api.posts_from_fb(TKN_ACCESS)

        if response['message'] is None:
            check_for_new_orders(response['data'])
        else :
            console_log = response['message']
            consola_out.insert('end', console_log)

    def close_app():
        serial_conn.close_connection()
        v.destroy()

    b = ttk.Button(v, text="Respuesta", command=get_console_log)
    b.place(x=700, y=385)

    bCerrarS = ttk.Button(v, text="Cerrar",
                          command=close_app, width=12)
    bCerrarS.place(x=375, y=650)

    # console log
    consola_out = Text(v, height=10, width=90,border=3)
    consola_out.place(x=50, y=205)
    consola_out.insert('end', console_log)
    v.mainloop()





App()

