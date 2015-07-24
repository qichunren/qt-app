$(function(){
    console.log("Document init.");
    


    // $.getJSON( "/stations.json", function( data ) {
    //   var items = [];
    //     console.log(data);
    //   $.each( data.stations, function( key, val ) {
    //     items.push( "<button id='" + key + "' type='button' class='btn btn-default station_item'>" + val + "</button>" );
    //   });

    //   $("#stations_group").html(items.join(" "));
    // });

  // Station Model
  // ----------

  // Our basic **Station** model has `name`, `order`, and `passed` attributes.
  var Station = Backbone.Model.extend({



    // Default attributes for the todo item.
    defaults: function() {
      return {
        name: "empty todo...",
        order: Stations.nextOrder(),
        passed: false
      };
    },

    // Toggle the `passed` state of this todo item.
    toggle: function() {
      this.save({passed: !this.get("passed")});
    }

  });


  // Station Collection
  // ---------------

  // The collection of stations is backed by *localStorage* instead of a remote
  // server.
  var StationList = Backbone.Collection.extend({

    // Reference to this collection's model.
    model: Station,

    url: "http://localhost:8000/stations.json",

    parse: function(data) {
    	return data.stations;
  	},

    // Save all of the todo items under the `"todos-backbone"` namespace.
    //localStorage: new Backbone.LocalStorage("todos-backbone"),

    // Filter down the list of all todo items that are finished.
    passed: function() {
      return this.where({passed: true});
    },

    // Filter down the list to only todo items that are still not finished.
    remaining: function() {
      return this.where({passed: false});
    },

    // We keep the Todos in sequential order, despite being saved by unordered
    // GUID in the database. This generates the next order number for new items.
    nextOrder: function() {
      if (!this.length) return 1;
      return this.last().get('order') + 1;
    },

    // Todos are sorted by their original insertion order.
    comparator: 'order'

  });

  // Create our global collection of **Todos**.
  var Stations = new StationList;  

// Todo Item View
  // --------------

  // The DOM element for a todo item...
  var StationView = Backbone.View.extend({

    //... is a list tag.
    tagName:  "li",
    className: "station",

    // Cache the template function for a single item.
    template: _.template($('#station-item-template').html()),

    // The DOM events specific to an item.
    events: {
      "click .toggle"   : "togglePassed"
    },

    // The TodoView listens for changes to its model, re-rendering. Since there's
    // a one-to-one correspondence between a **Todo** and a **TodoView** in this
    // app, we set a direct reference on the model for convenience.
    initialize: function() {
      //this.listenTo(this.model, 'change', this.render);
      //this.listenTo(this.model, 'destroy', this.remove);
    },

    // Re-render the titles of the todo item.
    render: function() {
      this.$el.html(this.template(this.model.toJSON()));
      //this.$el.toggleClass('passed', this.model.get('passed'));
      return this;
    },

    // Toggle the `"done"` state of the model.
    togglePassed: function() {
      this.model.toggle();
    }

  });  

  // The Application
  // ---------------

  // Our overall **AppView** is the top-level piece of UI.
  var AppView = Backbone.View.extend({

    // Instead of generating a new element, bind to the existing skeleton of
    // the App already present in the HTML.
    el: $("#routelist_ul"),

    // At initialization we bind to the relevant events on the `Todos`
    // collection, when items are added or changed. Kick things off by
    // loading any preexisting todos that might be saved in *localStorage*.
    initialize: function() {
   		this.collection = Stations;
    	this.listenTo(Stations, 'sync', this.render);



    },

	render: function() {
		console.log("this.collection", this.collection.length);		
	    this.collection.each(function(model) {
	      var item = new StationView({model: model});
	      this.$el.append(item.render().$el);
	    }, this);

    	return this;
  },

  });

  // Finally, we kick things off by creating the **App**.
  var App = new AppView;
      	Stations.fetch();

});
