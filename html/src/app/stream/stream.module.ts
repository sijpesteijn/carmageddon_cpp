import { NgModule } from '@angular/core';
import { StreamComponent } from './stream.component';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
@NgModule({
    imports: [
        CommonModule,
        FormsModule
    ],
    exports: [
        StreamComponent
    ],
    declarations: [
        StreamComponent
    ]
})
export class StreamModule {

}