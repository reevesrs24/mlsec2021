import base64

def main():
    
    f = open("phishing_samples_2021//01.html")
    lines = f.readlines()

    code_str = ''.join([line for line in lines if line != '\n' ])
    code_str = base64.b64encode(code_str)
    print(code_str)

if __name__=='__main__':
    main()