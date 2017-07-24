import { Component, ViewChild } from '@angular/core';
import { CarObserver, ObserverService, Roi } from '../observer.service';
import { StreamComponent } from '../../stream/stream.component';
@Component({
    selector: 'traffic-light',
    template: require('./traffic-light.html'),
    styles: [require('./traffic-light.scss')]
})
export class TrafficLightObserverComponent {
    @ViewChild(StreamComponent)
    private stream: StreamComponent;
    private observer: CarObserver;
    private interval = 1;

    constructor(private observerService: ObserverService) {}

    ngAfterViewInit() {
        this.observerService.getObserver('traffic_light').subscribe(data => {
           this.observer = data;
           setTimeout(() => 500);
        });
    }

    private setRoi() {
        this.stream.theRoi = this.observer.roi;
    }

    private updateRoi(event: any) {
        this.observer.roi = event;
        this.observerService.saveObserver('traffic_light', this.observer).subscribe(observer => this.observer = observer);
    }

    private updateObserver() {
        this.observer.active =  (Number(this.observer.active));
        this.observerService.saveObserver('traffic_light', this.observer).subscribe(observer => this.observer = observer);
    }

    private resetObserver() {
        this.observer.condition_achieved = 0;
        this.updateObserver();
    }
}