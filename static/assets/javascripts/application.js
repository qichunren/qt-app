$(function(){
    console.log("Document init.");


    $.getJSON( "/stations.json", function( data ) {
      var items = [];
        console.log(data);
      $.each( data.stations, function( key, val ) {
        items.push( "<button id='" + key + "' type='button' class='btn btn-default station_item'>" + val + "</button>" );
      });

      $("#stations_group").html(items.join(" "));
    });
});
