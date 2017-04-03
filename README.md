# simpleTLD
give thanks to Zdenek Kalal
```
    $./install.sh                      

   import TLD                         
   TLD = TLD.Tracker(1)   
   TLD.tracking((100, 100, 200, 200))        
   while True:                        
        print TLD.getData()           
        time.sleep(0.1)                        
   TLD.clearTracking()                
   TLD.close()                        
```

