<?php 
    $fr = fopen("../assets/config.ini", "r");
    $config = fread($fr, filesize("../assets/config.ini"));
    if($config == 1) {
        echo "<script>window.scrollTo(0,screen.height+1000);</script>";
    }
?>
<script src="//code.jquery.com/jquery.min.js"></script>
<script>
function runWrite() {
    $.ajax({
        url: "write.php",
        type: "post",
        data: $("#main_form").serialize(),
    }).done(function(data) {
        document.getElementById('co').innerHTML = data;
        window.scrollTo(0,screen.height+1000);
    });
}
</script>
<script>
function Enter_Check(){
    if(event.keyCode == 13){
        runWrite();
        document.getElementById('default_focus').value = "";
    }
}
</script>