import facebook

class Api():
    @classmethod
    def posts_from_fb(self, access_token):
        msg = None
        data = list()
        try:
            graph = facebook.GraphAPI(access_token=access_token)
            profile_posts = graph.get_connections(id='me', connection_name='posts')
        except facebook.GraphAPIError as e:
            msg = f"ERROR! : {str(e)}"

        for post in profile_posts['data']:
            value = post['message'] if 'message' in post else None 
            if value is not None:
                #print(post['message'])
                data.append(value)

        result = {"message" : msg, "data" : data}
        
        return result 