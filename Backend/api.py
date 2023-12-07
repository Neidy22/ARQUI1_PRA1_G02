# from flask import Flask
# from main import Main
# app = Flask(__name__)


# @app.route("/")
# def welcome():
#     resp = {
#         "message": "La aplicación se ha conectado"
#     }
#     return resp

# # @app.route("/posts", methods = ['GET'])
# # def get_posts():
# #     data = Main.posts_from_fb()
# #     resp = {
# #         "message" : "Nueva petición",
# #         "data" : data
# #     }
# #     return resp 

# @app.route("/posts", methods = ['GET'])
# def get_posts():
#     response = requests.get('https://graph.facebook.com/v18.0/{user-id}/posts', params={'access_token': 'YOUR_ACCESS_TOKEN'})
#     # Get the JSON response
#     json_response = response.json()
#     # Print the posts
#     resp = {
#         "message" : "Nueva petición",
#         "data" : json_response
#     }
#     for post in json_response['data']:
#         value = post['message'] if 'message' in post else None 
#         if value is not None:
#             print(post['message'])
#     return resp



# if __name__ == "__main__":
#     host ='0.0.0.0'
#     port = '5000'
#     app.run(host=host, port=port)
import facebook


class Api():
    @classmethod
    def posts_from_fb(self, access_token):
        graph = facebook.GraphAPI(access_token=access_token)
        profile_posts = graph.get_connections(id='me', connection_name='posts')
        

        for post in profile_posts['data']:
            value = post['message'] if 'message' in post else None 
            if value is not None:
                print(post['message'])

        return profile_posts['data']