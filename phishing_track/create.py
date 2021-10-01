import csv
import base64
import struct
import requests

from random import randrange



def crawl_alexa_top_sites():

    with open('majestic_million.csv', mode ='r') as file:   
    
        # reading the CSV file
        csvFile = csv.DictReader(file)
        count = 0
        # displaying the contents of the CSV file
        for lines in csvFile:
            # print(lines['Domain'])
            
            if count == 50:
                break

            r = requests.get("https://{}".format(lines['Domain']))
            # print(r.text)
            data = r.text.encode('utf8') 
            #with open("01.html", 'wb') as f:
            #    f.write(data)

            
            r = requests.post(url='https://api.mlsec.io/api/phish/submit_sample?api_token=<api token>&model=6',
                            data=data,
                            headers={'Content-Type': 'application/octet-stream'})
            res_json = r.json()
            if res_json['p_mod_06'] <= 0.1:
                print("{} => {}".format(lines['Domain'], res_json['p_mod_06']))
                break
            else:
                print("{} => {}".format(lines['Domain'], res_json['p_mod_06']))
            
            count += 1
    


def create_random_data():
    f = open("entropy.txt", "wb")
    size = 100000

    for i in range(size):
        f.write(struct.pack("B", randrange(256)))



def convert_html_to_base64_string():
    f = open("phishing_samples_2021//03_orig.html")
    lines = f.readlines()

    code_str = ''.join([line for line in lines if line != '\n' ])
    code_str = base64.b64encode(code_str)
    f2 = open("encoded.txt", "wt")

    f2.write("<script id=\"yo\" class=\"{}\" type=\"text/javascript\" src=\"/etc.titan.dexterlibs/homepage/clientlibs/publish.combined.fp-421c4c081baf214852bd975d300f5d39.js\" defer></script>".format(code_str))

def main():
    convert_html_to_base64_string()
    #crawl_alexa_top_sites()
   

if __name__=='__main__':
    main()

