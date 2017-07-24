import {
    AfterViewInit, Component, ElementRef, EventEmitter, HostListener, Input, Output, ViewChild
} from '@angular/core';
import { Roi } from '../observers/observer.service';

interface Point {
    x: number;
    y: number;
}

@Component({
    selector: 'stream',
    template: require('./stream.html'),
    styles: [require('./stream.scss')]
})
export class StreamComponent implements AfterViewInit {
    private reloadInterval: any;
    @Input('roi')
    set theRoi(roi: Roi) {
        // console.log(roi);
        if (roi) {
            this.roi = roi;
            this.setRoi();
        }
    }
    @Input('interval')
    set interval(interval: number) {
        this._interval = interval;
        clearInterval(this.reloadInterval);
        setTimeout(() => this.startReload(), 500);
    }
    private _interval = 1;
    private roi: Roi;
    @ViewChild('roi') roiElem;
    @ViewChild('webcam') webcamElem;
    @Output('onChange') changeEmitter = new EventEmitter();
    private streamUrl = 'http://carmageddon.dev/camera/snapshot/' + new Date();
    private mouseDown = false;

    @HostListener('mousedown', ['$event'])
    onMouseDown(event: any) {
        this.mouseDown = true;
        const point = this.getPoint(event);
        this.roi = {
            x: point.x,
            y: point.y,
            width: 0,
            height: 0
        };
        this.setRoi();
    }

    @HostListener('mouseup', ['$event'])
    onMouseUp(event: any) {
        this.mouseDown = false;
        this.changeEmitter.emit(this.roi);
    }

    @HostListener('mousemove', ['$event'])
    onMouseMove(event: any) {
        if (this.mouseDown) {
            const point = this.getPoint(event);
            this.roi.width  = point.x - this.roi.x;
            this.roi.height = point.y - this.roi.y;
            this.setRoi();
        }
    }

    @HostListener('ondragstart', ['$event'])
    onDragstart(event: any) {
        return false;
    }

    ngAfterViewInit() {
        this.startReload();
    }

    private setRoi() {
        if (this.roiElem) {
            this.roiElem.nativeElement.style.top    = this.roi.y + 'px';
            this.roiElem.nativeElement.style.height = this.roi.height + 'px';
            this.roiElem.nativeElement.style.left   = this.roi.x + 'px';
            this.roiElem.nativeElement.style.width  = this.roi.width + 'px';
        }
    }

    private getPoint(event: any): Point {
        const ev = event || window.event; //Moz || IE
        const point = { x: 0, y: 0};
        if (ev.pageX) { //Moz
            point.x = ev.layerX;
            point.y = ev.layerY;
        } else if (ev.clientX) { //IE
            point.x = ev.clientX + document.body.scrollLeft;
            point.y = ev.clientY + document.body.scrollTop;
        }
        return point;
    }

    private startReload() {
        console.log(this._interval * 1000);
        this.reloadInterval = setInterval(() => {
            this.streamUrl = 'http://carmageddon.dev/camera/snapshot/' + new Date();
        }, (this._interval * 1000));
    }
}