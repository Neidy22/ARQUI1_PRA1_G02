import facebook

PROD_1 = "galleta 1"
PROD_2 = "galleta 2"
PROD_3 = "galleta 3"

class Api():
    @classmethod
    def posts_from_fb(self, access_token):
        msg = None
        output_data = dict()
        
        try:
            graph = facebook.GraphAPI(access_token=access_token)
            profile = graph.get_connections(id='me', connection_name='posts')
            profile_posts = profile['data']

            for i in range (len(profile_posts) - 1, 0) :
                value = profile_posts[i]['message'] if 'message' in post else None 
                if value is not None and (value.lower() == PROD_1 or value.lower() == PROD_2 or value.lower() == PROD_3):
                    output_data[post['id']] = post['message']
                    println(output_data[post['id']])
                    
        except facebook.GraphAPIError as e:
            msg = f"ERROR! : {str(e)}"

    
        result = {"message" : msg, "data" : output_data}
        
        return result 

 
