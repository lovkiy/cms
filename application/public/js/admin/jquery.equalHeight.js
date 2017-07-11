// make sure the $ is pointing to JQuery and not some other library
    (function($){
        // add a new method to JQuery

        $.fn.equalHeight = function() {
            // find the tallest height in the collection
            // that was passed in (.column)
            this.each(function(){
                thisHeight = $(this).outerHeight();
				sideHeight = $("#main").outerHeight();
                if(thisHeight > sideHeight){
                    $("#main").height(thisHeight);
				}
				else{
                    $(this).height(sideHeight);
				}
            });
        }
    })(jQuery);