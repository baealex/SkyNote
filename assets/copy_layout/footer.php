<?php 
    $fr = fopen("../assets/config.ini", "r");
    $config = fread($fr, filesize("../assets/config.ini"));
    if($config == 1) {
        echo "<script>window.scrollTo(0,screen.height+9999);</script>";
    }
?>
<script src="//code.jquery.com/jquery.min.js"></script>
<script src="/assets/main.js"></script>