import facebook

PROD_1 = "galleta1"
PROD_2 = "galleta2"
PROD_3 = "galleta3"

class Api():
    @classmethod
    def posts_from_fb(self, access_token):
        msg = None
        output_data = dict()
        
        try:
            graph = facebook.GraphAPI(access_token=access_token)
            profile = graph.get_connections(id='me', connection_name='posts')
            profile_posts = profile['data']
            print("bandera1")
            print(len(profile_posts))
            for i in range (0,len(profile_posts) - 1) :
                value = profile_posts[i]['message'] if 'message' in profile_posts[i] else None 
                print("el valor de value es:", value)
                if value is not None and (value.lower() == PROD_1 or value.lower() == PROD_2 or value.lower() == PROD_3):
                    print("bandera5")
                    output_data[profile_posts[i]['id']] = profile_posts[i]['message']
                    print(output_data[profile_posts[i]['id']])
            print("bandera2")        
        except facebook.GraphAPIError as e:
            msg = f"ERROR! : {str(e)}"

    
        result = {"message" : msg, "data" : output_data}
        
        return result 

 
