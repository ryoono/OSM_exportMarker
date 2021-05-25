/*
* http://unguis.cre8or.jp/web/6341
* ↑ほぼコピペ
* https://jslob.repop.jp/2017/06/getjsonjson.html
* ↑JSONの同期
*/

window.onload = function () {

  var geojsonFeature = [];

  var r1;
  var r2;

  //getJSONを同期させる ( getJSONは非同期のためエラーが発生する )
  $.ajaxSetup({async: false});
  $.getJSON("../documents/data.json", function(data){
    for(var i in data){
      r1 = data[i].lng;
      r2 = data[i].lat;
      geojsonFeature[i] = {
        "type": "Feature",
        "properties": {
          "popupContent": r1 + ", " + r2
        },
        "geometry": {
          "type": "Point",
          "coordinates": [r1, r2]
        }
      }
      //alert('lng:' + r1 + ' ' + isNaN(r1) + ' lat:' + r2 + ' ' + isNaN(r2) );
    }
  });
  $.ajaxSetup({async: true});

  // 地図のデフォルトの緯度経度と拡大率
  var map = L.map('map').setView([ r2, r1], 12);

  // 描画する(Copyrightは消しちゃダメよ)
  var tileLayer = L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',{
    attribution: '© <a href="http://osm.org/copyright">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>',
    maxZoom: 19
  });
  tileLayer.addTo(map);
  L.geoJson(
    geojsonFeature,
    {
      onEachFeature: function(feature, layer){
        if (feature.properties && feature.properties.popupContent) {
          layer.bindPopup(feature.properties.popupContent);
        }
      }
    }
  ).addTo(map);
}
