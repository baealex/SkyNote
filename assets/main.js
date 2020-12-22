function runWrite(isSource=false) {
    $.ajax({
        url: "/write.php",
        type: "POST",
        data: {
            is_source: isSource,
            date: location.pathname.replace(/\//g, ''),
            memo: isSource ? $('textarea[name=source]').val() : $('input[name=memo]').val()
        }
    }).done(function(data) {
        document.getElementById('co').innerHTML = data;
		$('textarea[name=source]').val('');
        window.scrollTo(0,screen.height+9999);
    });
}

function Enter_Check() {
    if(event.keyCode == 13){
        runWrite();
        document.getElementById('default_focus').value = "";
    }
}