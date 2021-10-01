# Machine Learning Security Evasion Competition 2021 ([mlsec2021](https://mlsec.io/))
## Anti-Phishing Evasion Track

The dawn of the digital age has unleashed the Captain Ahab's upon the sea's of the cyber world and its great white whale is root on your machine.  While most of the time many play the role of the great white whale attempting to thwart the ever relenting Ahab's of the world from trying to harpoon their way into networks via specially crafted phishing sites, but in this rare case the roles have been reversed.  10 phishing samples are supplied and the goal of each participant ois to devise a method to bypass the 7 ml models trained to detect phioshing sites.  Every method must recreate an exact pixel for pixel representaion of the phishing site within a Chromium based browser running within  the competition's sandbox.  So with these simple rules set let the phishing begin.

First and foremost sspecial thanks to [Dr. Hyrum Anderson](https://twitter.com/drhyrum?lang=en) from Microsoft and [Zoltan Balazs](https://twitter.com/zh4ck?lang=en) from CUJO AI for organizing this one of kind competition.  Also a shout out to the sponsors who helped support and make this compettion possible [CUJO AI](https://twitter.com/CUJOAI), [Microsoft](https://twitter.com/Microsoft), [MRG Effitas](https://twitter.com/mrgeffitas), [NVIDIA](https://twitter.com/nvidia) and [VMRay](https://twitter.com/vmray).

## 1. Strategy ##
The overall strategy to defeat the anti-phishing models combined a base64 encoding of the phishing site which would then be embedded and self-extracted within a benign template.  In order to achieve FUD this strategy was broken down into 3 distinct parts.
1. Devise method utlizing javascript to recreate the phishing page
2. Find benign html template which would bypass all 7 anti-phishing models
3. Incrementally combine the deployment method with the benign html template

Overall I was aiming for a plug and play method which could be used for every phsihing site and one which would mitigate the overall manual configuration needed to fully bypass the models.

## 2. Deployment Method ##

In order to deploy the base64 encoded phishing site a method would need to be devised to extract and overlay the benign template with the phishing site.  The `src` HTML attribute intially seemed to be the most promising method since a bae64 encoded string could be converted to a `text/html` blob and injected into an element with this attribute.  Doing a little research led to an assortment of HTML tags that utilized this attribute in some capacity.  
<br>
<br>
<p align="center">
<img src="phishing_track/images/html_src.PNG" width=85% height=85%>
</p>
<br>
<br>

After some trial and error it became evident that the only viable HTML elements that would recreate the original phishing site with a high degree of fidelity were the `iframe` and `embed` tags.  This method was tested with some simple javascript and an iframe within an HTML file.  The "junk" or "benign" elements within the file would be effectively removed and replaced with an iframe that would render the phishing site in its place.  
<br>

```javascript
<script>
    document.getElementById('junk').style.display = 'none';
    let s = decodeURIComponent(escape(window.atob(<base64 encoded file>))
    let blob = new Blob([s], {type : "text/html"});

    var reader = new FileReader();

    reader.addEventListener("loadend", function(e){
        document.getElementById("test").src = e.srcElement.result;
    });

    reader.readAsDataURL(blob)
</script>
```

<br>
<br>
While this method appeared to be fulfilling the requisite technical needs for this method to be viable there was however a fatal flaw that would ultimately lead to scrapping of this technique.
<br>
<br>
<p align="center">
<img src="phishing_track/images/01.gif" width=85% height=85%>
</p>
<br>
<br>
