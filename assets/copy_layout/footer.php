<?php 
    $fr = fopen("../assets/config.ini", "r");
    $config = fread($fr, filesize("../assets/config.ini"));
        if($config == 1) {
        echo "<script>window.scrollTo(0,screen.height+1000);</script>";
    }
?>