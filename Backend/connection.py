import serial

ERROR_MESSAGE = "error"
DONE_MESSAGE = "done"
PROD_1 = "galleta 1"
PROD_2 = "galleta 2"
PROD_3 = "galleta 3"

class Connection():

    def __init__(self):
        self.conn = None
        
    def new_connection(self, com_port, baud_rate):
        response = False
        try:
            self.conn = serial.Serial(com_port,baud_rate)
            if not self.conn.isOpen():
                self.conn.open()
            response = True
        except TimeoutError:
            self.conn = None
            
        return response
        
    def close_connection(self):
        msg = None
        try:
            self.conn.close()
            msg = "Conexión cerrada"
        except TimeoutError:
            msg = "ERROR! No se pudo cerrar la conexión"
        return msg

    def check_for_new_orders(self, data, oldData):
        msg = "No hay nuevas órdenes"
        if (len(data) > oldData):
            for i in range(len(data) - 1, oldData):
                msg = self.send_new_order(data[i])
                if msg.lower() == ERROR_MESSAGE:
                    break

                while True:
                    # here are the arduino response types
                    print(msg)
                    break  
        return msg   

    def send_new_order(self, id):
        msg = None
        try:
            # send the new order id to the arduino
            if id.lower() == PROD_1 :
                self.conn.write(b'1')
            elif id.lower() == PROD_2 :
                self.conn.write(b'2')
            elif id.lower() == PROD_3 :
                self.conn.write(b'3')
            else :
                # invalid product id
                self.conn.write(b'0') 
                
            # wait for the arduino response for my request
            while True:
                msg = self.conn.readline()
                if msg != None:
                    break

        except TimeoutError:
            msg = "Error"
        
        return msg 


