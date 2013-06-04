(function($, Drupal)
{
	var map = new BMap.Map(Drupal.settings.bmap.container);
  	Drupal.bmap = Drupal.bmap || {
  		data:[],
  		init:function(){
  			this.setCenter();
  			this.addControl();
  		},
  		setCenter: function(){
  			var poi = new BMap.Point(105.404, 35.915);
  			map.centerAndZoom(poi, 5);
  		},
  		reset: function(){
  			map.clearOverlays();
  			this.setCenter();
  		},
  		phpSetData: function() {
  			this.data = Drupal.settings.bmap.data;
  		},
  		jsSetData: function(data) {
  			this.data = data;
  		},
  		addControl: function(){
		    map.enableScrollWheelZoom();
		    var ctrl_nav = new BMap.NavigationControl({anchor:BMAP_ANCHOR_TOP_LEFT,type:BMAP_NAVIGATION_CONTROL_LARGE});
		    map.addControl(ctrl_nav);
		    var ctrl_sca = new BMap.ScaleControl({anchor:BMAP_ANCHOR_BOTTOM_LEFT});
		    map.addControl(ctrl_sca);
  		},
      getXyByAddress: function(address){
        var _this = this;
        var myGeo = new BMap.Geocoder();
        myGeo.getPoint(address, function(point){
          if (point) {
            $('.bmap_form_x').val(point.lng);
            $('.bmap_form_y').val(point.lat);
          }
        });
      },
  		make: function(){
  			var _this = this;
  			for (var i in this.data) {
					var point = new BMap.Point(this.data[i]['x'], this.data[i]['y']);
          if (point) {
            this.data[i].point = point;
  					_this.addPoint(this.data[i]);
          }
  			}
  		},
      addPoint: function(data) {
        var searchInfoWindow = null;
        searchInfoWindow = new BMapLib.SearchInfoWindow(map, data.description, {
                title  : data.name,
                width  : 290,
                height : 105,
                panel  : "panel",
                enableAutoPan : true,
                enableSendToPhone : false,
                searchTypes   :[
                    BMAPLIB_TAB_SEARCH,
                    BMAPLIB_TAB_TO_HERE,
                    BMAPLIB_TAB_FROM_HERE
                ]
            });
        var marker = new BMap.Marker(data.point);
        marker.addEventListener("click", function(e){
            searchInfoWindow.open(marker);
        })
        map.addOverlay(marker);
      }
  	}
  Drupal.ajax.prototype.commands.bmapGetXY = function(ajax, response, status)
  {
    Drupal.bmap.getXyByAddress(response.data);
  };
	Drupal.ajax.prototype.commands.bmapPreview = function(ajax, response, status)
	{
		Drupal.bmap.reset();
		Drupal.bmap.jsSetData(response.data);
		Drupal.bmap.make();
	};
  Drupal.bmap.init();
}(jQuery, Drupal));
